#pragma once
#include "Puyo.h"
#include <SDL.h>
enum PUYOROTATESTATE { RIGHTP, BELOWP, LEFTP, BEYONDP };

class PuyoMov :public Puyo
{
public:

		PuyoMov(int color, int* time_fall);
		~PuyoMov();
		int* getPtrAuXSlow();
		int* getPtrAuYSlow();
		bool* getPtrBool();
		void update();

protected:
	PUYOROTATESTATE Move ;
/*	void Down();
	void DownMov();
	void Left();
	void LeftMov();
	void Right();
	void RightMov();*/

	void initCoord();
	void move2();
	void move();
	void moveA();
	void moveD();
	
};

