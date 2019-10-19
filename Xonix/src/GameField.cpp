#include "../include/GameField.h"

GameField::GameField(): gameMap(nullptr)
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

	enemyCount = rand() % 6 + 5 + 1;// rand(5, 10) + 1(side)

	entities = new Entity*[enemyCount];

	for (int i = 0; i < enemyCount - 1; i++)
	{
		entities[i] = new Enemy();
		entities[i]->init(gameMap, enums::TileType::Enemy);
	}
	entities[enemyCount - 1] = new Enemy();
	entities[enemyCount - 1]->init(gameMap, enums::TileType::EnemySide);
}

GameField::~GameField()
{

}

Scene* GameField::update()
{
	for (int i = 0; i < enemyCount; i++)
	{
		entities[i]->update();
	}
	return this;
}

void GameField::render(SDL_Renderer* renderer)
{
	static int height = Config::getConfig().windowHeight / 18;
	static int width = Config::getConfig().windowWidth / 18;

	SDL_Rect dstRect = { 0, 0, 18, 18 };

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
}

bool GameField::init(SDL_Window* window)
{
	ResourceManager::getManager().init(SDL_GetRenderer(window));
	return true;
}
