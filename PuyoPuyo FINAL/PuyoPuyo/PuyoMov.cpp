#include "PuyoMov.h"
PuyoMov::PuyoMov(int color,int* time_f)
{
	this->time_fall = time_f;
	l_timer_mov = new LTimer();
	l_timer_fall = new LTimer();
	Init(color);
	
}
PuyoMov::~PuyoMov()
{
	FreeTime();
	FreeTexture();
}
int * PuyoMov::getPtrAuXSlow()
{
	return &Position_x_matriz;
}
int * PuyoMov::getPtrAuYSlow()
{
	return &Position_y_matriz;
}
bool * PuyoMov::getPtrBool()
{
	return &StateDown;
}
void PuyoMov::initCoord()
{
	Move = RIGHTP;//Start right side
	coordX = INIT_PUYO_GRAPH_X+PUYO_SIZE; coordY = INIT_PUYO_GRAPH_Y;
	AsigCoord();
	Position_x_matriz = INI_SPACE_MATRIZ_X+1;//Where have to X start in matriz
	Position_y_matriz = INI_SPACE_MATRIZ_Y;//Where have to Y start in matriz
}
void PuyoMov::update()
{
	AutoDown();
	if (StateDown != false)
	{
		move();
	}
}
void PuyoMov::move2()
{
	SDL_PumpEvents();
	const Uint8 * keys = SDL_GetKeyboardState(NULL);
	//CAN DO THE MOV JUST WHEN THE TIME IS MORE THANT DELAY  AND EVALUE THE STATE FALL OF PUYOMOV
	if (l_timer_mov->getTicks() > PUYO_MOV_DELAY  /*&& Color != PUYO_BLACK*/)
	{
		if (keys[SDL_SCANCODE_S] && Position_y_matriz < MATRIZ_GAME_H)
		{
			Down();
			l_timer_mov->start();
		}
		if (keys[SDL_SCANCODE_A] && Position_x_matriz > 0)
		{
			Left();
			l_timer_mov->start();
		}
		if (keys[SDL_SCANCODE_D] && Position_x_matriz < MATRIZ_GAME_W)
		{
			Right();
			l_timer_mov->start();
		}
	}
	AsigCoord();
}
void PuyoMov::move()
{

		AsigCoord();
		SDL_PumpEvents();
		const Uint8 * keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_SPACE] && l_timer_mov->getTicks() > PUYO_MOV_DELAY )
		{
			int X = *ptrPuyoMovX;
			int Y = *ptrPuyoMovY;
			if (coordX - PUYO_SIZE == X && coordY == Y)//RIGHT
			{
				Move = RIGHTP;
				moveA();
			}
			if (coordX + PUYO_SIZE == X && coordY == Y)//left
			{
				Move = LEFTP;
				moveA();
			}
			if (coordY - PUYO_SIZE == Y && coordX == X)//Down
			{
				Move = BELOWP;
				moveA();
			}
			if (coordY + PUYO_SIZE == Y && coordX  == X)//Beyond
			{
				Move = BEYONDP;
				moveA();
			}
		}
		/*if (keys[SDL_SCANCODE_D] && l_timer_mov->getTicks() > PUYO_MOV_DELAY)
		{
			//moveD();
		}*/
		if (l_timer_mov->getTicks() > PUYO_MOV_DELAY)
		{
			move2();
		}
		
}
void PuyoMov::moveA()
{
	if (l_timer_mov->getTicks() > PUYO_MOV_DELAY)
	{
		switch (Move)
		{
		
		case BEYONDP:
			if (Position_x_matriz > 0)
			{
				if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz - 1] == 0)
				{
					Move = LEFTP;
					coordX = coordX - PUYO_SIZE;
					coordY = coordY + PUYO_SIZE;
					Position_x_matriz -= 1;
					Position_y_matriz += 1;
					l_timer_mov->start();
				}
				break;
		case LEFTP:
			if (Position_y_matriz < MATRIZ_GAME_H-1)
			{
				if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz + 1] == 0)
				{
					Move = BELOWP;
					coordX = coordX + PUYO_SIZE;
					coordY = coordY + PUYO_SIZE;
					Position_x_matriz += 1;
					Position_y_matriz += 1;
					l_timer_mov->start();
				}
			}
			break;
		case BELOWP:
			if (Position_x_matriz < MATRIZ_GAME_W-1)
			{
				if (Matriz_GAME[Position_y_matriz - 1][Position_x_matriz + 1] == 0)
				{
					Move = RIGHTP;
					coordX = coordX + PUYO_SIZE;
					coordY = coordY - PUYO_SIZE;
					Position_x_matriz += 1;
					Position_y_matriz -= 1;
					l_timer_mov->start();
				}
			}
			break;
		case RIGHTP:
			if (Position_y_matriz > 0)
			{
				if (Matriz_GAME[Position_y_matriz - 1][Position_x_matriz - 1] == 0)
				{
					Move = BEYONDP;
					coordX = coordX - PUYO_SIZE;
					coordY = coordY - PUYO_SIZE;
					Position_x_matriz -= 1;
					Position_y_matriz -= 1;
					l_timer_mov->start();
				}
			}
			break;
			};

		}
	}
	AsigCoord();
}
void PuyoMov::moveD()
{
	if (l_timer_mov->getTicks() > PUYO_MOV_DELAY)
	{
		switch (Move)
		{
		case BEYONDP:
			if (Position_x_matriz < MATRIZ_GAME_W-1) 
			{	
				if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz + 1] == 0)
				{
					Move = RIGHTP;
					coordX = coordX + PUYO_SIZE;
					coordY = coordY + PUYO_SIZE;
					Position_x_matriz += 1;
					Position_y_matriz += 1;
					l_timer_mov->start();
				}
			}
			break;
		case RIGHTP:
			if (Position_y_matriz  < MATRIZ_GAME_H-1)
			{
				if (Matriz_GAME[Position_y_matriz + 1][Position_x_matriz - 1] == 0)
				{
					Move = BELOWP;
					coordX = coordX - PUYO_SIZE;
					coordY = coordY + PUYO_SIZE;
					Position_x_matriz -= 1;
					Position_y_matriz += 1;
					l_timer_mov->start();
				}
			}
			break;
		case BELOWP:
			if (Position_x_matriz > 0)
			{
				if (Matriz_GAME[Position_y_matriz - 1][Position_x_matriz - 1] == 0)
				{
					Move = LEFTP;
					coordX = coordX - PUYO_SIZE;
					coordY = coordY - PUYO_SIZE;
					Position_x_matriz -= 1;
					Position_y_matriz -= 1;
					l_timer_mov->start();
				}
			}
			break;
		case LEFTP:
			if (Position_y_matriz > 0)
			{
				if (Matriz_GAME[Position_y_matriz - 1][Position_x_matriz + 1] == 0)
				{
					Move = BEYONDP;
					coordX = coordX + PUYO_SIZE;
					coordY = coordY - PUYO_SIZE;
					Position_x_matriz += 1;
					Position_y_matriz -= 1;
					l_timer_mov->start();
				}
			}
			break;
		};
	}
	AsigCoord();
}

