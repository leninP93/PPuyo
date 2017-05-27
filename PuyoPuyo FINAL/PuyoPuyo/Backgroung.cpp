#include "Backgroung.h"
#include "ResourceManager.h"
#include "Manager.h"

Backgroung::Backgroung(SDL_Texture * tex)
{
	Init(tex);
}
Backgroung::~Backgroung()
{
	FreeTexture();
}
void Backgroung::update()
{
}
void Backgroung::draw()
{
	SDL_RenderCopy(Manager::getInstance()->getGRenderer(), gTexture, NULL, &dest);
}
void Backgroung::initCoord()
{
	dest.x = INIT_BACKGOUNG_POS_X;
	dest.y = INIT_BACKGOUNG_POS_Y;
}
void Backgroung::FreeTexture()
{
	gTexture = NULL;
}
void Backgroung::Init(SDL_Texture * tex)
{
	FreeTexture();
	initCoord();
	gTexture = tex;
	SDL_QueryTexture(gTexture, NULL, NULL, &dest.w, &dest.h);
}
