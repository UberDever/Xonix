#include "../include/GameField.h"

int GameField::levelCounter = 0;

GameField::GameField(int _skill): gameMap(nullptr), skill(_skill), isScreenSaver(false)
{
	static int height = Config::getConfig().windowHeight / 18;
	static int width = Config::getConfig().windowWidth / 18;

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
		isScreenSaver = true;
		skill = 6;
	}
	else
	{
		entityCount = levelCounter + 1 + 1; // 1(first enemy) + 1(side)
		if (skill < 9)
			skill++;
		levelCounter++;
	}
	
	entities = new Entity*[entityCount];

	for (int i = 0; i < entityCount - 1; i++)
	{
		entities[i] = new Enemy();
		entities[i]->init(gameMap, enums::TileType::Enemy);
	}
	entities[entityCount - 1] = new Enemy();
	entities[entityCount - 1]->init(gameMap, enums::TileType::EnemySide);
	player = new Player();
	player->init(gameMap, enums::TileType::Wall); // Для отсутствия отображения в main menu

	int frameT[9] = { 60, 55, 50, 40, 30, 25, 20, 17, 15 };
	frameTime = frameT[skill - 1];

	BonusManager::getManager().getMap() = gameMap;
}

GameField::~GameField()
{

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
		if (slowCounter % player->getPar()["Slow"] == 0)
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
		unsigned acc = player->getPar()["Acceleration"];
		for (unsigned i = 0; i < acc && !isScreenSaver; i++)
		{
			player = player->update();
			if (player == nullptr)
			{
				delete this;
				return nullptr;
			}
		}
		BonusManager::getManager().update();
		time = SDL_GetTicks();
	}
	return this;
}

void GameField::render(SDL_Renderer* renderer)
{
	static int height = Config::getConfig().windowHeight / 18;
	static int width = Config::getConfig().windowWidth / 18;

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
	BonusManager::getManager().render(renderer);
}

bool GameField::init(SDL_Window* window)
{
	return true;
}
