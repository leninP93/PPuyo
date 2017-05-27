#pragma once
#include "Backgroung.h"
#include "LTimer.h"
#include <vector>
#include "Global.h"
#include "Label.h"
class State
{
public:

	State();
	~State();
	virtual bool update(std::string textureText);
	virtual void draw();
	void FreeText();
	
protected:
	virtual void init();
	Backgroung* bg = NULL;
	Label* textoOver = NULL;

};

