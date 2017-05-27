#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

class Backgroung
{
public:
	Backgroung(SDL_Texture * tex);
	~Backgroung();
	void update();
	void draw();
	void initCoord();
	void FreeTexture();
protected:
	SDL_Texture* gTexture;
	SDL_Rect dest;

	void Init(SDL_Texture * tex);
};

