#include "../include/GameField.h"

int GameField::levelCounter = 0;
int GameField::width = Config::getConfig().windowWidth / 18;
int GameField::height = Config::getConfig().windowHeight / 18;

GameField::GameField(std::unordered_map<std::string, unsigned int>* _par, int _skill): gameMap(nullptr), skill(_skill), par(nullptr)
{
	gameMap = new enums::TileType* [height];
	for (int i = 0; i < (height); i++)
	{
		gameMap[i] = new enums::TileType[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i < 2 || i > height - 3)
			{
				gameMap[i][j] = enums::TileType::Wall;
			}
			else if (j < 2 || j > width - 3)
			{
				gameMap[i][j] = enums::TileType::Wall;
			}
			else
			{
				gameMap[i][j] = enums::TileType::Void;
			}
		}
	}

	if (skill == 0)
	{
		entityCount = rand() % 6 + 5 + 1;// rand(5, 10) + 1(side)
		skill = 6;
	}
	else
	{
		entityCount = levelCounter + 1 + 1; // 1(first enemy) + 1(side)
		if (skill < 9)
			skill++;
		levelCounter++;
	}

	if (par == nullptr)
	{
		par = new std::unordered_map<std::string, unsigned int>();
		constexpr int GAME_PARAMETERS = 5;
		par->reserve(GAME_PARAMETERS);
		std::string names[] = { "Life", "Time", "Score", "Acceleration", "Slow" };
		unsigned values[] = { 3, 100, 0, 1, 1 };
		for (int i = 0; i < GAME_PARAMETERS; i++)
		{
			(*par)[names[i]] = values[i];
		}
	}
	
	entities = new Entity*[entityCount];

	int frameT[9] = { 60, 55, 50, 40, 30, 25, 20, 17, 15 };
	frameTime = frameT[skill - 1];

	for (int i = 0; i < entityCount - 1; i++)
	{
		entities[i] = new Enemy();
		entities[i]->init(gameMap, enums::TileType::Enemy);
	}
	entities[entityCount - 1] = new Enemy();
	entities[entityCount - 1]->init(gameMap, enums::TileType::EnemySide);
	player = new Player(par);
	player->init(gameMap, enums::TileType::PlayerSide);
}

GameField::~GameField()
{
	for (int i = 0; i < height; i++)
	{
		delete gameMap[i];
	}
	delete gameMap;
	for (int i = 0; i < entityCount; i++)
	{
		delete entities[i];
	}
	delete entities;
	delete player;
}

Scene* GameField::handleEvent(const enums::GameEvent& event)
{
	player->handleEvent(event);
	return this;
}

Scene* GameField::update()
{
	auto static time = SDL_GetTicks();
	static unsigned slowCounter = 1;

	/*if (time + 1000 < SDL_GetTicks())
	{
		unsigned lastedTime = --player->getPar()["Time"];
		std::cout << lastedTime << std::endl;
		if (lastedTime == 0)
		{
			delete this;
			return nullptr;
		}
	}*/

	if (time + frameTime < SDL_GetTicks())
	{
		if (slowCounter % (*par)["Slow"] == 0)
		{
			for (int i = 0; i < entityCount; i++)
			{
				entities[i] = entities[i]->update();
			}
			slowCounter = 1;
		}
		else
		{
			slowCounter++;
		}
		unsigned acc = (*par)["Acceleration"];
		for (unsigned i = 0; i < acc; i++)
		{
			player = player->update();
			if (player == nullptr)
			{
				delete this;
				return nullptr; // TODO: New scene "leaderboard"
			}
		}
		time = SDL_GetTicks();
	}
	return this;
}

void GameField::render(SDL_Renderer* renderer)
{
	static SDL_Rect dstRect = { 0, 0, 18, 18 };

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			SDL_RenderCopy(renderer, ResourceManager::getManager().sprites[(int)gameMap[i][j]], nullptr, &dstRect);
			dstRect.x += 18;
		}
		dstRect.x = 0;
		dstRect.y += 18;
	}
	dstRect.x = 0;
	dstRect.y = 0;
	GraphicManager::getManager().drawText(0, height * 18, 0xff, 0xff, 0xff, 32, "Score:");
}

Scene* GameField::newLevel()
{
	delete this;
	if (skill > 9)
		return nullptr; // TODO: New scene "leaderboard"
	return new GameField(par, skill + 1);
}

bool GameField::isFilled()
{
	static float S = width * height;
	int counter = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (gameMap[i][j] == enums::TileType::Wall)
				counter++;
		}
	}
	return (counter / S) > 90;
}
