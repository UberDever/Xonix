#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class ResourceManager
{
private:

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&) = delete;

	ResourceManager();
	~ResourceManager();
public:

	SDL_Texture* mainSprites[7]; //PlayerOnSide, PlayerOnVoid, trail, wall, void, enemySide, enemyField
	SDL_Texture* bonusSprites[7]; //6 types + 1 void (for association)

public:
	static ResourceManager& getManager()
	{
		static ResourceManager instance;
		return instance;
	}

	bool init(SDL_Renderer*);
};