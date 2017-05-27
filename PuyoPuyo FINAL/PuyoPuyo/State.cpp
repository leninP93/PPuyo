#include "State.h"

State::State()
{
	init();
}
State::~State()
{
	FreeText();
}
bool State::update(std::string textureText)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	textoOver->loadFromRenderedText(50, 10, textureText);
	if (keys[SDL_SCANCODE_RETURN])
	{
		return true;
	}
	else return false;
}
void State::draw()
{
	textoOver->Draw();
}
void State::FreeText()
{
	if (textoOver)
	{
		delete textoOver;
		textoOver = NULL;
	}
}
void State::init()
{
	textoOver = new Label();
}
