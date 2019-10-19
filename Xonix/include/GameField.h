#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "ResourceManager.h"
#include "Config.h"
#include "Enums.h"
#include "Scene.h"
#include "Entity.h"

class GameField : public Scene
{
private:
	enums::TileType **gameMap;
	Entity** entities;

	int enemyCount;

public:

	GameField();
	~GameField();

	Scene* handleEvent(const enums::GameEvent& event) override { return nullptr; };
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;

	bool init(SDL_Window* window);
};
