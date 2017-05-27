#include "search.h"
#include "ResourceManager.h"

search::search()
{
	
}
search::~search()
{

}
int search::Searching(int X, int Y, SMOVE STATESEARCH, bool BEYOND, bool BELOW, bool RIGHT, bool LEFT,bool DELETE)
{
	int Counter = 0;
	switch (STATESEARCH)
	{
	   case INIS:
		   BEYOND = STOP(X,Y);
		   BELOW = SBOTTOM(X,Y);
		   RIGHT = SRIGHT(X,Y);
		   LEFT = SLEFT(X,Y);
		   ValueXInitialPuyo = X;
		   ValueYInitialPuyo = Y;
		   if (BEYOND != false)
		   {
			   Counter = Counter + Searching(X, (Y - 1),TOPS , BEYOND, BELOW, RIGHT, LEFT, DELETE);
		   }
		   if (LEFT != false)
		   {
			   Counter = Counter + Searching((X - 1), Y, LEFTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
		   }
		   if (RIGHT != false)
		   {
			   Counter = Counter + Searching((X + 1), Y, RIGHTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
		   }
		   if (BELOW != false)
		   {
			   Counter = Counter + Searching(X, (Y + 1), BOTTOMS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
		   }
		   break;
	   case TOPS:
		   if (AreTheSame(X, Y) != true)
		   {
			   BEYOND = STOP(X, Y);
			   RIGHT = SRIGHT(X, Y);
			   LEFT = SLEFT(X, Y);
			   BELOW = true;
			   if (BEYOND != false)
			   {
				   Counter = Counter + Searching(X, (Y - 1), TOPS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
			   if (LEFT != false)
			   {
				   Counter = Counter + Searching((X - 1), Y, LEFTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
			   if (RIGHT != false)
			   {
				   Counter = Counter + Searching((X + 1), Y, RIGHTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
		   }
		   break;

	   case RIGHTS:
		   if (AreTheSame(X, Y) != true)
		   {
			   RIGHT = SRIGHT(X, Y);

			   if (BEYOND == false)
			   {
				   BEYOND = STOP(X, Y);
				   if (BEYOND != false)
				   {
					   Counter = Counter + Searching(X, (Y - 1), TOPS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
				   }
			   }
			   if (BELOW == false)
			   {
				   BELOW = SBOTTOM(X, Y);
				   if (BELOW != false)
				   {
					   Counter = Counter + Searching(X, (Y + 1), BOTTOMS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
				   }
			   }
			   if (RIGHT != false)
			   {
				   BELOW = SBOTTOM(X, Y);//SEARCH IF ARE SOME COLOR SAME BELOW
				   BEYOND = SBOTTOM(X, Y);//SEARCH IF ARE SOME COLOR SAME BEYOND
				   Counter = Counter + Searching((X + 1), Y, RIGHTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
		   }
		   break;

	   case BOTTOMS:
		   if (AreTheSame(X, Y) != true)
		   {
			   BELOW = SBOTTOM(X, Y);
			   RIGHT = SRIGHT(X, Y);
			   LEFT = SLEFT(X, Y);
			   BEYOND = true;
			   if (BELOW != false)
			   {
				   Counter = Counter + Searching(X, (Y + 1), BOTTOMS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
			   if (LEFT != false)
			   {
				   Counter = Counter + Searching((X - 1), Y, LEFTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
			   if (RIGHT != false)
			   {
				   BELOW = SBOTTOM(X, Y);
				   BELOW = SBOTTOM(X, Y);
				   Counter = Counter + Searching((X + 1), Y, RIGHTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
		   }
		   break;

	   case LEFTS:
		   if (AreTheSame(X, Y) != true)
		   {
			   LEFT = SLEFT(X, Y);
			   if (BEYOND == false)
			   {
				   BEYOND = STOP(X, Y);
				   if (BEYOND != false)
				   {
					   Counter = Counter + Searching(X, (Y - 1), TOPS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
				   }
			   }
			   if (BELOW == false)
			   {
				   BELOW = SBOTTOM(X, Y);
				   BEYOND = SBOTTOM(X, Y);
				   if (BELOW != false)
				   {
					   Counter = Counter + Searching(X, (Y + 1), BOTTOMS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
				   }
			   }
			   if (LEFT != false)
			   {
				   Counter = Counter + Searching((X - 1), Y, LEFTS, BEYOND, BELOW, RIGHT, LEFT, DELETE);
			   }
		   }
		   break;

	}
	if(DELETE == true)
	{
		Matriz_Game[Y][X] = 0;
	}

	return Counter+1;
}
bool search::Reorder()
{
	int color = 0;
	bool Need_Reorder = false;
	//STARTED FROM THE END TO THE INITIO OF MATRIZ
	for (int i = (MATRIZ_GAME_H - 1); i > 0;i--)
	{
		for (int j = 0;j < MATRIZ_GAME_W;j++)
		{
			if (Matriz_Game[i][(j)] == 0)//IF WE FOUND A 0
			{
				if (Matriz_Game[(i - 1)][(j)] != 0 && Matriz_Game[(i - 1)][(j)] != PUYO_BLACK)//If beyond are some value diferent of 0 that mean we have to to change of position
				{
					//Save the color
					color = Matriz_Game[(i - 1)][j];
					Matriz_Game[i][(j)] = color;// new position of the color
					Matriz_Game[(i - 1)][(j)] = 0; // free the last position
					Need_Reorder = true;
				}
			}
		}
	}
	return Need_Reorder;
}
bool search::SearchPuyo()//Search if found some combo
{
	int Combo = 0;
	bool Is_there_Combo = false;
	for (int i = (MATRIZ_GAME_H - 1); i > 0;i--)//STARTED FROM THE END TO THE INITIO OF MATRIZ
	{
		for (int j = 0; j < MATRIZ_GAME_W; j++)
		{
			if (Matriz_Game[i][j] != 0 )
			{
				Combo = Searching(j, i, INIS, false, false, false, false, false);
				if (Combo >= 4)//If valor is more or same thant 4
				{
					ScoreUser += Combo;
					//if we found a combo , the program started to search again but now  we tell him that need to free the space
					Searching(j, i, INIS, false, false, false, false, true);
					Is_there_Combo = true; //there are a combo
					
				}
			}
		}
	}
	return Is_there_Combo;//return if found a combo or not
}
bool search::isFullIniSpace()
{
	//Search in intial position to found if the matriz is full
	if (Matriz_Game[INI_SPACE_MATRIZ_Y][INI_SPACE_MATRIZ_X] != 0 || Matriz_Game[INI_SPACE_MATRIZ_Y][INI_SPACE_MATRIZ_X+1] != 0)
	{
		return true;

	}else return false;
}
void search::setMatrizGame(int ** Matriz_Game)
{
	this->Matriz_Game = Matriz_Game;
}
int * search::getValuelScoreUser()
{
	return &ScoreUser;
}
bool search::SBOTTOM(int x, int y)
{
	if (y + 1 < MATRIZ_GAME_H)
	{
		if (Matriz_Game[(y+1)][x] == Matriz_Game[y][x])
		{
			return true;
		}
		else return false;

	}else return false;
}
bool search::SRIGHT(int x, int y)
{
	if(x + 1 < MATRIZ_GAME_W)
	{
		if (Matriz_Game[y][(x + 1)] == Matriz_Game[y][x])
		{
				 return true;
		}return false;

	}else return false;
}
bool search::SLEFT(int x , int y)
{
	if ((x - 1) >= 0)
	{
		if (Matriz_Game[y][(x - 1)] == Matriz_Game[y][x])
		{
			 return true;
		}else return false;

	}else return false;
}
bool search::STOP(int x , int y)
{
	if((y - 1) >= 0)
	{
		if (Matriz_Game[(y - 1)][x] == Matriz_Game[y][x])
		{
			 return true;
		}return false;

	}else return false;
}
bool search::AreTheSame(int x ,int y)
{
	if (x == ValueXInitialPuyo && y == ValueYInitialPuyo && Matriz_Game[y][x] != 0)
	{
		return true;

	}else return false;
}
