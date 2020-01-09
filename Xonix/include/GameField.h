#pragma once

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "ResourceManager.h"
#include "GraphicManager.h"
#include "LeaderBoard.h"
#include "Bonus.h"
#include "Config.h"
#include "Enums.h"
#include "Scene.h"
#include "Entity.h"

class GameField : public Scene
{
private:
	static int levelCounter;
	static int width;
	static int height;

	enums::TileType** gameMap;
	Player* player;
	Entity** entities;

	std::string name;
	SDL_Renderer* objRenderer;

	int frameTime;
	int entityCount;
	int skill;
	std::unordered_map<std::string, unsigned int>* par;

public:

	GameField(std::unordered_map<std::string, unsigned int>* _par, int _skill);
	~GameField();

	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;

	bool init(SDL_Renderer* renderer) override;
	Scene* newLevel();
	bool isFilled();
	int querryScore() { return (*par)["Score"]; }
};
