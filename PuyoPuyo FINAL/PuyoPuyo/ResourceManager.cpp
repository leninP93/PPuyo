#include "ResourceManager.h"
#include "Manager.h"
#include "global.h"
ResourceManager * ResourceManager::ms_pInstance = NULL;

ResourceManager * ResourceManager::GetInstance()
{
	if (ms_pInstance == NULL)
	{
		ms_pInstance = new ResourceManager;
	}

	return ms_pInstance;
}
void ResourceManager::DestroyInstance()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = NULL;
	}
}
void ResourceManager::unloadResources()
{
	SDL_DestroyTexture(gTextureBackgroung);
	gTextureBackgroung = NULL;
	//Red
	for(int i = 0; i < gTexturePuyoRed.size(); i++)
	{
		if (gTexturePuyoRed[i])
		{
			SDL_DestroyTexture(gTexturePuyoRed[i]);
			gTexturePuyoRed[i] = NULL;

		}
	}
	gTexturePuyoRed.clear();
	//Blue
	for (int i = 0; i < gTexturePuyoBlue.size(); i++)
	{
		if (gTexturePuyoBlue[i])
		{
			SDL_DestroyTexture(gTexturePuyoBlue[i]);
			gTexturePuyoBlue[i] = NULL;

		}
	}
	gTexturePuyoBlue.clear();
	//Black
	for (int i = 0; i < gTexturePuyoBlack.size(); i++)
	{
		if (gTexturePuyoBlack[i])
		{
			SDL_DestroyTexture(gTexturePuyoBlack[i]);
			gTexturePuyoBlack[i] = NULL;

		}
	}
	gTexturePuyoBlack.clear();
	//Green
	for (int i = 0; i < gTexturePuyoGreen.size(); i++)
	{
		if (gTexturePuyoGreen[i])
		{
			SDL_DestroyTexture(gTexturePuyoGreen[i]);
			gTexturePuyoGreen[i] = NULL;

		}
	}
	gTexturePuyoGreen.clear();
	//Yellow
	for (int i = 0; i < gTexturePuyoYellow.size(); i++)
	{
		if (gTexturePuyoYellow[i])
		{
			SDL_DestroyTexture(gTexturePuyoYellow[i]);
			gTexturePuyoYellow[i] = NULL;

		}
	}
	gTexturePuyoYellow.clear();
	//Phant
	for (int i = 0; i < gTexturePuyoPhant.size(); i++)
	{
		if (gTexturePuyoPhant[i])
		{
			SDL_DestroyTexture(gTexturePuyoPhant[i]);
			gTexturePuyoPhant[i] = NULL;

		}
	}
	gTexturePuyoYellow.clear();
}
bool ResourceManager::LoadResources()
{
	//Init Textures	
	if (!loadTextures())
	{
		printf("Load texture Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
bool ResourceManager::loadTextures()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	/*****************************
	* LOAD TEXTURE PUYOS Puyos *
	******************************/

	//Puyo Rojo
	for (int i = 0; i <= NUM_PUYO_TEXTURES; i++)
	{
		gTexturePuyoRed.push_back(loadTexture("img/red/prefix_"+ std::to_string(i)+ ".png"));
		
		if (gTexturePuyoRed.back() == NULL)
		{
			printf("Couldnt load puyo %s\n", SDL_GetError());
			return false;
		}
	}
	//Puyo Blue
	for (int i = 0; i <= NUM_PUYO_TEXTURES; i++)
	{
		gTexturePuyoBlue.push_back(loadTexture("img/blue/prefix_" + std::to_string(i) + ".png"));
		
		if (gTexturePuyoBlue.back() == NULL)
		{
			printf("Couldnt load puyo %s\n", SDL_GetError());
			return false;
		}
	}
	//Puyo Green
	for (int i = 0; i <= NUM_PUYO_TEXTURES; i++)
	{
		gTexturePuyoGreen.push_back(loadTexture("img/green/prefix_" + std::to_string(i) + ".png"));
		
		if (gTexturePuyoGreen.back() == NULL)
		{
			printf("Couldnt load puyo: %s\n", SDL_GetError());
			return false;
		}
	}
	//Puyo Yellow
	for (int i = 0; i <= NUM_PUYO_TEXTURES; i++)
	{
		gTexturePuyoYellow.push_back(loadTexture("img/yellow/prefix_" + std::to_string(i) + ".png"));
		
		if (gTexturePuyoYellow.back() == NULL)
		{
			printf("Couldnt load puyoe: %s\n", SDL_GetError());
			return false;
		}
	}
	//Puyo Black
	for (int i = 0; i <= NUM_PUYO_TEXTURES; i++)
	{
		gTexturePuyoBlack.push_back(loadTexture("img/black/prefix_" + std::to_string(i) + ".png"));

		if (gTexturePuyoBlack.back() == NULL)
		{
			printf("Couldnt load puyoe: %s\n", SDL_GetError());
			return false;
		}
	}
	//Phant
	for (int i = 0; i <= NUM_PUYO_TEXTURES; i++)
	{
		gTexturePuyoPhant.push_back(loadTexture("img/phant/prefix_" + std::to_string(i) + ".png"));

		if (gTexturePuyoPhant.back() == NULL)
		{
			printf("Couldnt load puyoe: %s\n", SDL_GetError());
			return false;
		}
	}
	//THE BACKGROUNG
	gTextureBackgroung = loadTexture("img/Bgg.png");
	if (gTextureBackgroung == NULL)
	{
		printf("Couldnt load puyo: %s\n", SDL_GetError());
		return false;
	}

}
SDL_Texture * ResourceManager::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Le decimos a SDL cual será el color transparente, en este caso 255,0,0 es cpolor rojo
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 0));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Manager::getInstance()->getGRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

SDL_Texture* ResourceManager::getPuyoRedTextureAt(int i) {

	return gTexturePuyoRed.at(i);
}

SDL_Texture * ResourceManager::getPuyoGreenTextureAt(int i)
{
	return gTexturePuyoGreen.at(i);
}

SDL_Texture * ResourceManager::getPuyoYellowTextureAt(int i)
{
	return gTexturePuyoYellow.at(i);
}
SDL_Texture * ResourceManager::getPuyoBlackTextureAt(int i)
{
	return gTexturePuyoBlack.at(i);
}
SDL_Texture * ResourceManager::getPuyoPhantTextureAt(int i)
{
	return gTexturePuyoPhant.at(i);
}
SDL_Texture * ResourceManager::getPuyoBlueTextureAt(int i)
{
	return gTexturePuyoBlue.at(i);
}

SDL_Texture * ResourceManager::getBackgroundTexture()
{
	return gTextureBackgroung;
}



