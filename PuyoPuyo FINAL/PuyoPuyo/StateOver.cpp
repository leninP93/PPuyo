#include "StateOver.h"

StateOver::StateOver()
{
	init();
}
StateOver::~StateOver()
{
	FreeText();
}
void StateOver::init()
{
	textoOver = new Label();
}
