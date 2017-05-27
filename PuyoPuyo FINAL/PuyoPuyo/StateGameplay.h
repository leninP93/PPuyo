#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Puyo.h"
#include "PuyoMov.h"
#include "PuyoMold.h"
#include "search.h"
#include "State.h"
class StateGameplay :public State
{
public:
	StateGameplay();
	~StateGameplay();

	bool update();
	void draw();
	void ScoreGame();
	int getWinner();
    void Winner(int PuyoUser,int PuyoPhant);
private:
	int*  Score = NULL;
	int winner = 0;
	int ScorePhanton = 0;
	void PhantonB();
	int New_color_Puyo;
	int New_color_PuyoMov;
	void NextPuyo();
	int Colorear();
	void FreeMatriz();
	void drawPuyos();
	bool Refresh();
	bool EffectDown = false;
	int PUYO_FALL_DELAY = 800;
	search* SearcP =  NULL;
	Puyo* puyo = NULL;
	PuyoMov* puyo2 = NULL;
	PuyoMold* puyoExt = NULL;
	PuyoMold* puyoPhant = NULL;

	int** Matriz_Game = NULL; 
	void loadMatriz();
	 void init();

};

