#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Global.h"
class ResourceManager
{
private:
	ResourceManager() {}
	~ResourceManager() {}
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	ResourceManager(const ResourceManager &) {}
	ResourceManager& operator =(const ResourceManager &) {}

public:
	static ResourceManager * GetInstance();
	static void DestroyInstance();
	void unloadResources();
	bool LoadResources();
	SDL_Texture *getPuyoRedTextureAt(int i);
	SDL_Texture *getPuyoGreenTextureAt(int i);
	SDL_Texture *getPuyoYellowTextureAt(int i);
	SDL_Texture *getPuyoBlueTextureAt(int i);
	SDL_Texture *getPuyoBlackTextureAt(int i);
	SDL_Texture *getPuyoPhantTextureAt(int i);
	SDL_Texture * getBackgroundTexture();

private:
	
	static ResourceManager * ms_pInstance;
	std::vector<SDL_Texture *> gTexturePuyoPhant;
	std::vector<SDL_Texture *> gTexturePuyoRed;
	std::vector<SDL_Texture *> gTexturePuyoBlue;
	std::vector<SDL_Texture *> gTexturePuyoGreen;
	std::vector<SDL_Texture *> gTexturePuyoYellow;
	std::vector<SDL_Texture *> gTexturePuyoBlack;
	SDL_Texture* gTextureBackgroung;
	
	
	bool loadTextures();
	SDL_Texture * loadTexture(std::string path);

};

