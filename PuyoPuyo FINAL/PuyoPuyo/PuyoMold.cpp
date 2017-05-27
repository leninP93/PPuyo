#include "PuyoMold.h"
#include "ResourceManager.h"

PuyoMold::PuyoMold()
{
	l_timer_mov = new LTimer();
}
PuyoMold::PuyoMold(int x, int y, int color)
{
	l_timer_mov = new LTimer();

	coordX = x; coordY = y; 
	initDataPuyo(x, y, color);

	l_timer_mov->start();
	 Position_x_matriz = 0;
     Position_y_matriz = MATRIZ_GAME_H-1;
}
PuyoMold::~PuyoMold()
{
	FreeTime();
	FreeTexture();
}
int * PuyoMold::getPositionMatrizX()
{
	return &Position_x_matriz;
}
int * PuyoMold::getPositionMatrizY()
{
	return &Position_y_matriz;
}
void PuyoMold::initDataPuyo(int x, int y, int color)
{
	coordPuyoRect.x = x;
	coordPuyoRect.y = y;

	FreeTexture();
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
	case PUYO_PHANT:
		puyoTexture = ResourceManager::GetInstance()->getPuyoPhantTextureAt(0);
		Color = PUYO_BLACK;
		break;
	}
	SDL_QueryTexture(puyoTexture, NULL, NULL, &coordPuyoRect.w, &coordPuyoRect.h);
}
void PuyoMold::move()
{
	if (Position_x_matriz == MATRIZ_GAME_W-1 && Position_y_matriz == 0)
	{
		initCoord();
	}
	if (l_timer_mov->getTicks() > PUYO_MOV_PHANT && Position_x_matriz < MATRIZ_GAME_W-1)
	{
		coordX += PUYO_SIZE;
		Position_x_matriz +=1;
		l_timer_mov->start();
	}else if(l_timer_mov->getTicks() > PUYO_MOV_PHANT && Position_x_matriz == MATRIZ_GAME_W - 1)
			{ 
				coordY -= PUYO_SIZE; 
				coordX = INIT_BACKGOUNG_POS_X * 2; 
				Position_x_matriz = 0;
				Position_y_matriz -= 1;
				l_timer_mov->start();
			}
	AsigCoord();
}

void PuyoMold::update()
{
		move();
}

void PuyoMold::initCoord()
{
	coordX = INIT_BACKGOUNG_POS_X * 2; coordY = (INIT_BACKGOUNG_POS_Y + PUYO_SIZE)*MATRIZ_GAME_H;
	AsigCoord();
	Position_x_matriz = 0;
	Position_y_matriz = MATRIZ_GAME_H - 1;
}

