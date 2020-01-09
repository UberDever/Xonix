#include "../include/ResourceManager.h"


ResourceManager::ResourceManager() : mainSprites{nullptr}
{

}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < 7; i++)
	{
		SDL_DestroyTexture(mainSprites[i]);
	}
	for (int i = 0; i < 7; i++)
	{
		SDL_DestroyTexture(bonusSprites[i]);
	}
}

bool ResourceManager::init(SDL_Renderer* renderer)
{
	std::string names[] = { "void", "wall", "playerOnSide", "playerOnVoid", "playerTrail", "enemy", "enemySide", "bug" ,"Life",
	"Time", "Score", "Acceleration", "Slow", "Random"};
	SDL_Surface* temp = nullptr;
	for (int i = 0; i < 7; i++)
	{
		std::string tempS = "data/sprites/" + names[i] + ".png";
		if (temp = IMG_Load(tempS.c_str()))
		{
			mainSprites[i] = SDL_CreateTextureFromSurface(renderer, temp);
			SDL_FreeSurface(temp);
		}
		else
			return false;
	}
	for (int i = 0; i < 7; i++)
	{
		std::string tempS = "data/sprites/" + names[i + 7] + ".png";
		if (temp = IMG_Load(tempS.c_str()))
		{
			bonusSprites[i] = SDL_CreateTextureFromSurface(renderer, temp);
			SDL_FreeSurface(temp);
		}
		else
			return false;
	}
	return true;
}