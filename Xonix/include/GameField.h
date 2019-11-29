#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "ResourceManager.h"
#include "GraphicManager.h"
#include "Config.h"
#include "Enums.h"
#include "Scene.h"
#include "Entity.h"
#include "Bonus.h"

class GameField : public Scene
{
private:
	static int levelCounter;
	bool isScreenSaver;

	enums::TileType** gameMap;
	Player* player;
	Entity** entities;

	int frameTime;
	int entityCount;
	int skill;

public:

	GameField(int _skill);
	~GameField();

	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;

	bool init(SDL_Window* window);
};
