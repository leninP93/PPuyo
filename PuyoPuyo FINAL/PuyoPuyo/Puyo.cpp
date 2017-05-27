#include "Puyo.h"
#include "ResourceManager.h"
#include "Manager.h"

Puyo::Puyo(int color,int* time_f)
{
	this->time_fall = time_f;
	l_timer_mov = new LTimer();
	l_timer_fall = new LTimer();
	Init(color);

}
Puyo::~Puyo()
{
	FreeTime();
	FreeTexture();
}
void Puyo::Init(int color)
{
	FreeTexture();
	this->Color = color;
	switch (color)
	{
		case PUYO_RED:
			puyoTexture = ResourceManager::GetInstance()->getPuyoRedTextureAt(0);
			Color = PUYO_RED;
			break;
		case PUYO_GREEN:
			puyoTexture = ResourceManager::GetInstance()->getPuyoGreenTextureAt(0);
			Color = PUYO_GREEN;
			break;
		case PUYO_BLUE:
			puyoTexture = ResourceManager::GetInstance()->getPuyoBlueTextureAt(0);
			Color = PUYO_BLUE;
			break;
		case PUYO_YELLOW:
			puyoTexture = ResourceManager::GetInstance()->getPuyoYellowTextureAt(0);
			Color = PUYO_YELLOW;
			break;
		case PUYO_BLACK:
			puyoTexture = ResourceManager::GetInstance()->getPuyoBlackTextureAt(0);
			Color = PUYO_BLACK;
			break;
	}
	StateDown = true;
	initCoord();
	SDL_QueryTexture(puyoTexture, NULL, NULL, &coordPuyoRect.w, &coordPuyoRect.h);

	l_timer_mov->start();
	l_timer_fall->start();
}
void Puyo::FreeTime()
{
	if (l_timer_mov)
	{
		delete l_timer_mov;
		l_timer_mov = NULL;
	}
	if (l_timer_fall)
	{
		delete l_timer_fall;
		l_timer_fall = NULL;
	}
}
void Puyo::FreeTexture()
{
	puyoTexture = NULL;
}
void Puyo::update()
{
	AutoDown();
	if (StateDown != false)
	{
		move();
	}
}
void Puyo::draw()
{
	SDL_RenderCopy(Manager::getInstance()->getGRenderer(), puyoTexture, NULL, &coordPuyoRect); 
}
void Puyo::setValuePuyoMovPositionGraphX(float *X)
{
	this->ptrPuyoMovX = X;
}
void Puyo::setValuePuyoMovPositionGraphY(float *Y)
{
	this->ptrPuyoMovY = Y;
}
void Puyo::setValorPuyoPositionMatrizX(int * X)
{
	this->ptrPuyoPositionMatrizX = X;
}
void Puyo::setValorPuyoPositionMatrizY(int * Y)
{
	this->ptrPuyoPositionMatrizY = Y;
}
bool Puyo::getStateDown()
{
	return StateDown;
}
bool Puyo::IsBelow()
{
	int Y = *ptrPuyoPositionMatrizY;
	if (Y < Position_y_matriz)
	{
		return true;
	}
	else { return false; }
}
void Puyo::setPuyoBoolState(bool * State)
{
	ptrPuyoBool = State;
}
void Puyo::move()
{
		
		SDL_PumpEvents();
		const Uint8 * keys = SDL_GetKeyboardState(NULL);
		//CAN DO THE MOV JUST WHEN THE TIME IS MORE THANT DELAY  AND EVALUE THE STATE FALL OF PUYOMOV
		if (l_timer_mov->getTicks() > PUYO_MOV_DELAY /*&& Color != PUYO_BLACK*//*&& *ptrPuyoBool != false*/ )
		{
			if (keys[SDL_SCANCODE_DOWN] && Position_y_matriz < MATRIZ_GAME_H)
			{
				//if (*ptrPuyoPositionMatrizY <= Position_y_matriz)
				//{
					Down();//WHEN THE PUYOMOV IS BEYOND OR THE SAME Y POSITION OF PUYO   (pM2)   (pM2)(p1)
					//												                     (p1)
				//}
				//else{ DownMov(); }//WHEN PUYOMOV IS BELOW OF PUYO (p1)
				//                                                (pM2)
			}
			if (keys[SDL_SCANCODE_LEFT] && Position_x_matriz > 0)
			{
				//if (*ptrPuyoPositionMatrizX >= Position_x_matriz)
				//{
					Left();//WHEN THE PUYO IS ON RIGHT SIDE (p1)(pM2)
				//}
				//else { LeftMov(); }//WHEN THE PUYO IS ON LEFT SIDE (pM2)(p1)
			}
			if (keys[SDL_SCANCODE_RIGHT] && Position_x_matriz < MATRIZ_GAME_W)
			{
				//if (*ptrPuyoPositionMatrizX <= Position_x_matriz)
				//{
					Right();//WHEN THE PUYO IS ON THE LEFT SIDE OR THE SAME X  (pM2)(p1)
				//}
				//else { RightMov(); }//WHEN THE PUYO IS ON THE RIGH SIDE (p1)(pM2)
			}
		}
		AsigCoord();
}
void Puyo::initCoord()
{
	coordX = INIT_PUYO_GRAPH_X ; coordY = INIT_PUYO_GRAPH_Y;

	AsigCoord();
	Position_x_matriz = INI_SPACE_MATRIZ_X;
	Position_y_matriz = INI_SPACE_MATRIZ_Y;
}
void Puyo::AddMatriz(int** Matriz_Game)
{
	this->Matriz_GAME = Matriz_Game;
}
void Puyo::AutoDown()
{
	if (StateDown != false)
	{
		if (l_timer_fall->getTicks() > *time_fall)
		{
			if (Position_y_matriz < MATRIZ_GAME_H-1)
			{
				if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz] == 0)
				{
					Position_y_matriz = Position_y_matriz + 1;
					coordY += PUYO_FALL_DOWN;
					l_timer_fall->start();
				}else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }

			}else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }
		}
	}
}
float * Puyo::getPtrCoordX()
{
	return &coordX;
}

float * Puyo::getPtrCoordY()
{
	return &coordY;
}
void Puyo::AsigCoord()
{
	coordPuyoRect.x = coordX;
	coordPuyoRect.y = coordY;
}
void Puyo::Down()
{
	if (Position_y_matriz < MATRIZ_GAME_H - 1)
	{
		if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz] == 0)
		{
			if (coordY + PUYO_SIZE == *ptrPuyoMovY && coordX == *ptrPuyoMovX)
			{
			}
			else
			{
				Position_y_matriz = Position_y_matriz + 1;
				coordY += PUYO_FALL_DOWN;
				l_timer_mov->start();//Restar clock
			}
		}
		else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }
	}
	else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }
}
void Puyo::Left()
{
	if (Matriz_GAME[Position_y_matriz][Position_x_matriz - 1] == 0)
	{
		if (coordX - PUYO_SIZE == *ptrPuyoMovX && coordY == *ptrPuyoMovY)
		{
		}
		else {
			Position_x_matriz = Position_x_matriz - 1;
			coordX -= PUYO_SIZE;
			l_timer_mov->start();
		}
	}
}
void Puyo::Right()
{

	if (Matriz_GAME[Position_y_matriz][Position_x_matriz + 1] == 0)
	{
		if (coordX + PUYO_SIZE == *ptrPuyoMovX && coordY == *ptrPuyoMovY)
		{
		}
		else
		{
			Position_x_matriz = Position_x_matriz + 1;
			coordX += PUYO_SIZE;
			l_timer_mov->start();
		}
	}
}
/*
void Puyo::Down()
{
	int X = *ptrPuyoPositionMatrizX;
	int Y = *ptrPuyoPositionMatrizY;
	if (Position_y_matriz < MATRIZ_GAME_H - 1)
	{
		if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz] == 0)
		{
			Position_y_matriz = Position_y_matriz + 1;
			coordY += PUYO_FALL_DOWN;
			if (Matriz_GAME[Y + 1][X] == 0)
			{
				*ptrPuyoPositionMatrizY += 1;
				*ptrPuyoMovY += PUYO_FALL_DOWN;
			}
			l_timer_mov->start();//Restar clock
		}
		else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }
	}
	else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }
}*/
void Puyo::DownMov()
{
	int X = *ptrPuyoPositionMatrizX;
	int Y = *ptrPuyoPositionMatrizY;

	if (Y < MATRIZ_GAME_H - 1)
	{
		if (Matriz_GAME[Y + 1][X] == 0)
		{
			Position_y_matriz = Position_y_matriz + 1;
			//*ptrPuyoPositionMatrizY += 1;
			coordY += PUYO_FALL_DOWN;

			//*ptrPuyoMovY += PUYO_FALL_DOWN;
			l_timer_mov->start();

		}else{ StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }

	}else { StateDown = false; Matriz_GAME[Position_y_matriz][Position_x_matriz] = Color; }
}
/*
void Puyo::Left()
{
	int X = *ptrPuyoPositionMatrizX;
	int Y = *ptrPuyoPositionMatrizY;
	
		if (Matriz_GAME[Position_y_matriz][Position_x_matriz - 1] == 0 && Matriz_GAME[Y][X - 1] == 0)
		{
			Position_x_matriz = Position_x_matriz - 1;
			coordX -= PUYO_SIZE;
			//*ptrPuyoMovX -= PUYO_SIZE;
			//*ptrPuyoPositionMatrizX -= 1;
			l_timer_mov->start();
		}
	
}*/
void Puyo::LeftMov()
{
	int X = *ptrPuyoPositionMatrizX;
	int Y = *ptrPuyoPositionMatrizY;
	
		if (Matriz_GAME[Y][X - 1] == 0)
		{
			Position_x_matriz = Position_x_matriz - 1;
			coordX -= PUYO_SIZE;
			//*ptrPuyoMovX -= PUYO_SIZE;
			//*ptrPuyoPositionMatrizX -= 1;
			l_timer_mov->start();
		}
	
}
/*
void Puyo::Right()
{
	int X = *ptrPuyoPositionMatrizX;
	int Y = *ptrPuyoPositionMatrizY;
	
		if (Matriz_GAME[Position_y_matriz][Position_x_matriz + 1] == 0 && Matriz_GAME[Y][X + 1] == 0)
		{
			Position_x_matriz = Position_x_matriz + 1;
			coordX += PUYO_SIZE;
			*ptrPuyoMovX += PUYO_SIZE;
			*ptrPuyoPositionMatrizX += 1;
			l_timer_mov->start();
		}
}*/
void Puyo::RightMov()
{
	int X = *ptrPuyoPositionMatrizX;
	int Y = *ptrPuyoPositionMatrizY;

		if (Matriz_GAME[Y][X + 1] == 0)
		{
			Position_x_matriz = Position_x_matriz + 1;
			coordX += PUYO_SIZE;
			//*ptrPuyoMovX += PUYO_SIZE;
			//*ptrPuyoPositionMatrizX += 1;
			l_timer_mov->start();
		}
	
}

