#include "Manager.h"
#include "LTimer.h"
#include "Global.h"

#define ENABLE_FPS_LIMIT
#ifdef ENABLE_FPS_LIMIT
#endif


Manager * Manager::ms_pInstance = NULL;
SDL_Window * Manager::gWindow = NULL;
SDL_Renderer * Manager::gRenderer = NULL;

Manager * Manager::getInstance()
{
	if (ms_pInstance == NULL)
	{
		ms_pInstance = new Manager;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			exit(1);
		}
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			exit(1);
		}
		// Initialize SDL_ttf library
		if (TTF_Init() != 0)
		{
			SDL_Quit();
			exit(1);
		}
		//Create renderer for window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			exit(1);
		}

		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	}

	return ms_pInstance;
}

void Manager::DestroyInstance()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = NULL;
	}

}

bool Manager::update()
{
	bool isLive = true;
	setState(MAIN_MENU);
#ifdef ENABLE_FPS_LIMIT
	//The frames per second cap timer
	LTimer capTimer;
#endif

	int frameTicks = 0;
	while (isLive)
	{
		#ifdef ENABLE_FPS_LIMIT
				//Start cap timer
				capTimer.start();
		#endif
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) { isLive = false; } //DETERMINATE IF NEED QUIT THE GAME
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) { isLive = false; } //IF THE USER USE SCAPE RETURN FALSE AND THE GAME STOP
			}
		}
		//CLEAR THE WINDOW
		SDL_RenderClear(Manager::getInstance()->getGRenderer());

		switch (state)
		{
				case MAIN_MENU:
					if (!Main_Menu->update("PRESSS ENTER TO START"))
					{
						Main_Menu->draw();
					}
					else { setState(GAMEPLAY); }
					break;
				case GAMEPLAY:
					if (!gamplay_stage->update())//LOOK IF WE CAN CONTINIUD DRAWING
					{
						gamplay_stage->draw();
					}
					else{
						winner  =  gamplay_stage->getWinner();
						setState(OVER);
					}
					break;
				case IN_GAME_SUB_MENU:
					break;
				case OVER:
					if (winner == winUser)
					{
						if (!Over_game->update("User puyo winner press enter to try again"))
						{

							Over_game->draw();
						}
						else
						{
							setState(MAIN_MENU);
						}
					}
					else if(winner == WinPhant)
					{
						if (!Over_game->update("Phanton Puyo winner enter to try again"))
						{

							Over_game->draw();
						}
						else
						{
							setState(MAIN_MENU);
						}
					}
					else {
							if (!Over_game->update("Same Score try again"))
							{

								Over_game->draw();
							}
							else
							{
								setState(MAIN_MENU);
							}
						}
					
					break;
				case SCORE:
					break;
				case CREDITS:
					break;
				default:
					break;
		}
		//REFRESH THE WINDOW
		SDL_RenderPresent(gRenderer);
		#ifdef ENABLE_FPS_LIMIT
				//If frame finished early
				frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICKS_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
				}
		#else
				SDL_Delay(1);
		#endif

	}
	return isLive;
}
void Manager::setState(int newState)
{
	switch (state)
	{
	case MAIN_MENU:
		delete Main_Menu;
		Main_Menu = NULL;
		break;
	case GAMEPLAY:
		delete gamplay_stage;
		gamplay_stage = NULL;
		break;
	case OVER:
		delete Over_game;
		Over_game = NULL;
		break;
	case SCORE:
		break;
	case CREDITS:
		break;
	default:
		break;
	}

	switch(newState)
	{
	case MAIN_MENU:
		if(!Main_Menu)
			Main_Menu = new State();
		break;
	case GAMEPLAY:
		if (!gamplay_stage)
			gamplay_stage = new StateGameplay();
		break;
	case OVER:
		if(!Over_game)
		Over_game = new StateOver();
		break;
	case SCORE:
		break;
	case CREDITS:
		break;
	default:
		break;
	}

	state = newState;
}
