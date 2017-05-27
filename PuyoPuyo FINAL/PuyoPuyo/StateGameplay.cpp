#include "StateGameplay.h"
#include "ResourceManager.h"
StateGameplay::StateGameplay()
{
	srand(time(NULL)); //GENERATE A SEED
	init();
}
StateGameplay::~StateGameplay()
{
	if(puyo)
	{
		delete puyo;
		puyo = NULL;
	}
	if (puyo2)
	{
		delete puyo2;
		puyo = NULL;
	}
	if (bg)
	{
		delete bg;
		bg = NULL;
	}
	if (SearcP)
	{
		delete SearcP;
		SearcP = NULL;
	}
	if (puyoExt)
	{
		delete puyoExt;
		puyoExt = NULL;
	}
	FreeText();
	FreeMatriz();
}
void StateGameplay::NextPuyo()
{
	puyoExt->initDataPuyo(INIT_BACKGOUNG_POS_X+500, INIT_BACKGOUNG_POS_Y,New_color_Puyo);
	puyoExt->draw();
	puyoExt->initDataPuyo(INIT_BACKGOUNG_POS_X + 500, INIT_BACKGOUNG_POS_Y+ PUYO_SIZE, New_color_PuyoMov);
	puyoExt->draw();
}
int StateGameplay::Colorear()
{
	int LimiteI = LIMITCOLORBELOW;
	int LimiteS = LIMITCOLORBEYOND; 

	return LimiteI + rand() % ((LimiteS + 1) - LimiteI);
}
void StateGameplay::FreeMatriz()
{
	if (Matriz_Game)
	{
		for (int i = 0;i < MATRIZ_GAME_H;i++)
		{
				delete[] Matriz_Game[i];
		}
	}
	delete[] Matriz_Game;
	Matriz_Game = NULL;
}
void StateGameplay::loadMatriz()
{
	Matriz_Game = new int*[MATRIZ_GAME_H];
	for (int i = 0;i < MATRIZ_GAME_H;i++)
	{
		Matriz_Game[i] = new int[MATRIZ_GAME_W];
	}
	for (int i = 0;i < MATRIZ_GAME_H;i++)
	{
		for (int j = 0;j < MATRIZ_GAME_W;j++)
		{
			Matriz_Game[i][j] = 0;
		}
	}
}
void StateGameplay::init()
{
	loadMatriz();
	textoOver = new Label();
	SearcP = new search();
	puyo = new Puyo(Colorear(), &PUYO_FALL_DELAY);
	puyo2 = new PuyoMov(Colorear(), &PUYO_FALL_DELAY);
	bg = new Backgroung(ResourceManager::GetInstance()->getBackgroundTexture());
	puyoExt = new PuyoMold();

	puyoPhant = new PuyoMold(INIT_BACKGOUNG_POS_X * 2, (INIT_BACKGOUNG_POS_Y + PUYO_SIZE)*MATRIZ_GAME_H, PUYO_PHANT);//Fantasma
	//add matriz address
	SearcP->setMatrizGame(Matriz_Game);
	puyo->AddMatriz(Matriz_Game);
	puyo2->AddMatriz(Matriz_Game);

	puyo->setPuyoBoolState(puyo2->getPtrBool());
	//Puyo get the address of memory from puyo2 his coord from graphic puyo

	puyo->setValuePuyoMovPositionGraphX(puyo2->getPtrCoordX());//Obtener valor grafico
	puyo->setValuePuyoMovPositionGraphY(puyo2->getPtrCoordY());//Obtener valor grafico

	puyo2->setValuePuyoMovPositionGraphX(puyo->getPtrCoordX());//Get value grafic
	puyo2->setValuePuyoMovPositionGraphY(puyo->getPtrCoordY());//Get value grafic

	//Puyo get the address of memory from puyo2 his coord from matriz 
	puyo->setValorPuyoPositionMatrizX(puyo2->getPtrAuXSlow());
	puyo->setValorPuyoPositionMatrizY(puyo2->getPtrAuYSlow());

	New_color_Puyo = Colorear();
	New_color_PuyoMov = Colorear();
	Score = SearcP->getValuelScoreUser();
}
bool StateGameplay::update()
{
	bool StateLose = SearcP->isFullIniSpace(); //EVALUE IF THE MATRIZ IS FULL
	
	if(puyo->getStateDown() == false && puyo2->getStateDown() == false)
	{
		if (Refresh() == true)
		{}
		else{
				puyo2->Init(New_color_Puyo);
				puyo->Init(New_color_PuyoMov);
				New_color_Puyo = Colorear();
				New_color_PuyoMov = Colorear();
		     }
	}else if(puyo->IsBelow() == true)// IF THE PUYOMV IS BELOW OF PUYO
			{
				puyo->update();
				puyo2->update();
				puyoPhant->update();
				PhantonB();
			}else {
					puyo2->update();
					puyo->update();
					puyoPhant->update();
					PhantonB();
				  }
	while (SearcP->Reorder() != false) {}
	Winner(*Score,ScorePhanton);
	return StateLose;
}
void StateGameplay::draw()
{
	if (EffectDown == true)
	{
		bg->draw();
		drawPuyos();
		puyoPhant->draw();
		NextPuyo();
		ScoreGame();
	
	}
	else {
			bg->draw();
			puyo2->draw();
			puyo->draw();
			puyoPhant->draw();
			drawPuyos();
			NextPuyo();
			ScoreGame();
		
	    }
}
void StateGameplay::ScoreGame()
{
	//USer
	std::string tf = std::to_string(*Score);
	textoOver->loadFromRenderedText(INIT_BACKGOUNG_POS_X + 500, INIT_BACKGOUNG_POS_Y + PUYO_SIZE*2,"Score User: "+tf);
	textoOver->Draw();
	//Phanton
	std::string ll = std::to_string(ScorePhanton);
	textoOver->loadFromRenderedText(INIT_BACKGOUNG_POS_X + 500, INIT_BACKGOUNG_POS_Y + PUYO_SIZE * 3,"Score Phanton: " + ll);
	textoOver->Draw();
}
int StateGameplay::getWinner()
{
	return winner;
}
void StateGameplay::Winner(int PuyoUser, int PuyoPhant)
{
	if (PuyoUser > PuyoPhant)
	{
		winner = winUser;
	}else
	if (PuyoUser < PuyoPhant)
	{
		winner = WinPhant;
	}
	else { winner = Same; }
}
void StateGameplay::PhantonB()
{
	int *X = puyoPhant->getPositionMatrizX();
	int *Y = puyoPhant->getPositionMatrizY();
	int Color = Matriz_Game[*Y][*X];
	bool isCombo = false;
	for (int i = 1; i <= 5; i++)
	{
		Matriz_Game[*Y][*X] = i;
		int valor = SearcP->Searching(*X, *Y, INIS, false, false, false, false, false);
		if(valor == 4)
		{
			ScorePhanton += SearcP->Searching(*X, *Y, INIS, false, false, false, false, true);
			i = 6;
			puyoPhant->initCoord();
			isCombo = true;
		}else { isCombo = false; }
	}
	if (isCombo == false)
	{
		Matriz_Game[*Y][*X] = Color;
	}
}
void StateGameplay::drawPuyos()
{
	int IniX = PLAY_LEFT;
	int IniY = PLAY_TOP;

	for (int i = 0; i < MATRIZ_GAME_H; i++)
	{
		for (int j = 0; j < MATRIZ_GAME_W; j++)
		{
			//i is y  and j is x
			if(Matriz_Game[i][j] != 0)
			{
				puyoExt->initDataPuyo(IniX,IniY, (Matriz_Game[i][j]));
				puyoExt->draw();
			}
			// When we change of puyo , we add the puyo size to move in the next position on the windows
			IniX += PUYO_SIZE;
		}
		IniX = PLAY_LEFT; // Restar the X value
		IniY += PUYO_SIZE; // Move to the next Y Position
	}
}
bool StateGameplay::Refresh()
{
	bool Status = false;
	if (EffectDown == false)
	{
		Status = SearcP->SearchPuyo();
		if(Status == true)//If there are a combo , we're going to ordenizer matriz
		{
			EffectDown = SearcP->Reorder();
		}
	}
	else { EffectDown = SearcP->Reorder();  Status = true; }

	return Status;
}


