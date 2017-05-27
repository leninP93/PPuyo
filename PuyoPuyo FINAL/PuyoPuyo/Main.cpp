#include <stdio.h>
#include "Manager.h"
#include "ResourceManager.h"

int main(int argc, char* args[])
{
	ResourceManager::GetInstance()->LoadResources();
	
	Manager::getInstance()->update();

	ResourceManager::GetInstance()->unloadResources();
	ResourceManager::GetInstance()->DestroyInstance();
	Manager::getInstance()->DestroyInstance();
	return 0;
}