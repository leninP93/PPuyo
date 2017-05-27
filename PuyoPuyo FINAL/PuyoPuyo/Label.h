#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Global.h"
class Label
{
public:
	Label();
	~Label();
	void freeFont();
	bool loadFromRenderedText(int X , int Y ,std::string textureText);
	void LoadFont();
	void Draw();
private:
	SDL_Texture* textTexture = NULL;
	SDL_Rect coordTextRect;
	TTF_Font *gFont = NULL;
	SDL_Color textColor = { 0xff, 0, 0 };//Red
};

