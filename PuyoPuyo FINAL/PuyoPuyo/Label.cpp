#include "Label.h"
#include "Manager.h"


Label::Label()
{
	LoadFont();
}
Label::~Label()
{
	freeFont();
}
void Label::freeFont()
{
	if (textTexture != NULL)
	{
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
}
bool Label::loadFromRenderedText(int X, int Y,std::string textureText)
{
	//Get rid of preexisting texture
	freeFont();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

	coordTextRect.x = X;
	coordTextRect.y = Y;
	coordTextRect.w = textSurface->w;
	coordTextRect.h = textSurface->h;

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(Manager::getInstance()->getGRenderer(), textSurface);
		if (textTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
	
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return textTexture != NULL;
}
void Label::LoadFont()
{
	gFont = TTF_OpenFont("lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Oh My Goodness, an error : %s", TTF_GetError());
	}
}

void Label::Draw()
{
	SDL_RenderCopy(Manager::getInstance()->getGRenderer(), textTexture, NULL, &coordTextRect);
}
