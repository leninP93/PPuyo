#pragma once
#include "Global.h"

enum SMOVE{ RIGHTS, BOTTOMS, LEFTS, TOPS, INIS};
class search
{
public:
	search();
	~search();
	bool Reorder();
	bool SearchPuyo();
	bool isFullIniSpace();
	void setMatrizGame(int ** Matriz_Game);
	int*getValuelScoreUser();
	int Searching(int X, int Y, SMOVE StateSearch, bool BEYOND, bool BELOW, bool RIGHT, bool LEFT, bool Delete);
private:
	int ScoreUser = 0;
	bool AreTheSame(int x , int y);
	int ValueXInitialPuyo, ValueYInitialPuyo;
	int ** Matriz_Game ;
	bool SBOTTOM(int x, int y);
	bool SLEFT(int x, int y);
	bool SRIGHT(int x, int y);
	bool STOP(int x, int y);
};
