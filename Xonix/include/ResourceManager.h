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

	SDL_Texture* sprites[7]; //PlayerOnSide, PlayerOnVoid, trail, wall, void, enemySide, enemyField

public:
	static ResourceManager& getManager()
	{
		static ResourceManager instance;
		return instance;
	}

	bool init(SDL_Renderer*);
};