#pragma once
#include "Puyo.h"
class PuyoMold :public Puyo
{
public:
	PuyoMold();
	PuyoMold(int x,int y,int color);
	~PuyoMold();
	int* getPositionMatrizX();
	int* getPositionMatrizY();

	void initDataPuyo(int x, int y, int color);
	void move();
	void update();
	void initCoord();
};

