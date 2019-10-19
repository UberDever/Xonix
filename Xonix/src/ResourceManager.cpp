#include "../include/ResourceManager.h"


ResourceManager::ResourceManager() : sprites{nullptr}
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::init(SDL_Renderer* renderer)
{
	std::string names[] = { "void", "wall", "playerOnSide", "playerOnVoid", "playerTrail", "enemy", "enemySide" };
	SDL_Surface* temp = nullptr;
	for (int i = 0; i < 7; i++)
	{
		std::string tempS = "data/sprites/" + names[i] + ".png";
		if (temp = IMG_Load(tempS.c_str()))
		{
			sprites[i] = SDL_CreateTextureFromSurface(renderer, temp);
		}
		else
			return false;
	}
	return true;
}