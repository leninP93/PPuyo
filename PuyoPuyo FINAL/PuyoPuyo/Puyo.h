#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Global.h"
#include <time.h>
#include "LTimer.h"
class Puyo
{
public:
	Puyo() {};
	Puyo(int color,int* time_fall);
	~Puyo();

	void Init(int color);
	virtual void update();
	void draw();
	void  setValuePuyoMovPositionGraphX(float *X);//TO RECEIVE THE VALUE X FROM PUYOMOV OF POSITION ON THE WINDOWS
	void  setValuePuyoMovPositionGraphY(float *Y);//TO RECEIVE THE VALUE Y FROM PUYOMOV OF POSITION ON THE WINDOWS

	void  setValorPuyoPositionMatrizX(int* X);//TO RECEIVE THE VALUE X FROM PUYOMOV OF POSITION ON THE MATRIZ
	void  setValorPuyoPositionMatrizY(int* Y);//TO RECEIVE THE VALUE Y FROM PUYOMOV OF POSITION ON THE MATRIZ

	bool  getStateDown();//Return the value of the fall
	bool  IsBelow();//TO DETERMINARE IF PUYO IS BELOW OR BEYOND
	void setPuyoBoolState(bool* State);//RECEIVE THE VALUE OF THE STATE OF PUYOMOV
	void AddMatriz(int** Matriz_Game);//GET THE MATRIZ TO WORK

	float* getPtrCoordX();
	float* getPtrCoordY();

protected:
	bool StateDown = true;
	SDL_Texture* puyoTexture = NULL;
	SDL_Rect coordPuyoRect;
	
	void FreeTime();
	void FreeTexture();
	int* time_fall = NULL;
	int Color = 0;
	float coordX, coordY;
	int Position_x_matriz;
	int Position_y_matriz;

	float* ptrPuyoMovX = NULL;
	float* ptrPuyoMovY = NULL;
	
	virtual void move();
	virtual void initCoord();
	void AutoDown();
	void AsigCoord();
	int **Matriz_GAME = NULL;
	LTimer* l_timer_mov = NULL;
	LTimer* l_timer_fall = NULL;
	void Down();
	void Right();
	void Left();

private:
	
	void DownMov();
	void LeftMov();
	void RightMov();
	bool Flat_down;
	bool*   ptrPuyoBool = NULL;
	int*   ptrPuyoPositionMatrizX = NULL;
	int*   ptrPuyoPositionMatrizY = NULL;
};

