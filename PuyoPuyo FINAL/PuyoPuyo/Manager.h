#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "StateGameplay.h"
#include "StateOver.h"
#include "State.h"
class Manager
{

protected:
	Manager() {}
	~Manager() {}
	Manager(const Manager &) {}
	Manager& operator =(const Manager &) {}

public:
	static Manager * getInstance();
	static void DestroyInstance();

#ifdef USE_SOFTWARE_RENDER
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
#endif

	bool update();

	static SDL_Window* getGWindow() { return gWindow; }
	static SDL_Renderer* getGRenderer() { return gRenderer; }

	const Uint8* getKeysPressed() { return gkeys; }
	//float getDeltaTime();
protected:
	static Manager * ms_pInstance;

	//Ventana global a la que vamos a renderear
	static SDL_Window* gWindow;

	//Nuestro render global
	static SDL_Renderer* gRenderer;


	// La variable event de tipo evento de SDL nos servirá para monitorizar el teclado
	SDL_Event event;

	const Uint8 *gkeys;

	int state;
	
	void setState(int newState);
	int getState() {return state;}
	int winner = 0;
	StateGameplay* gamplay_stage;
	State* Main_Menu;
	StateOver* Over_game;
	
};

