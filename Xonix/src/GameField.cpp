#include "../include/GameField.h"

int GameField::levelCounter = 0;
int GameField::width = Config::getConfig().windowWidth / 18;
int GameField::height = Config::getConfig().windowHeight / 18;

GameField::GameField(std::unordered_map<std::string, unsigned int>* _par, int _skill): gameMap(nullptr), skill(_skill), par(_par), objRenderer(nullptr)
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
		entityCount = levelCounter + 3 + 1; // 3(first 3 enemy) + 1(side)
		if (skill < 9)
		{
			levelCounter++;
		}
		
	}

	if (par == nullptr)
	{
		par = new std::unordered_map<std::string, unsigned int>();
		constexpr int GAME_PARAMETERS = 5;
		par->reserve(GAME_PARAMETERS);
		std::string names[] = { "Life", "Time", "Score", "Acceleration", "Slow" };
		unsigned values[] = { 3, 99, 0, 1, 1 };
		for (int i = 0; i < GAME_PARAMETERS; i++)
		{
			(*par)[names[i]] = values[i];
		}
	}
	else
	{
		(*par)["Score"] += 15000 * (skill - 1);
		(*par)["Acceleration"] = 1;
		(*par)["Slow"] = 1;
		(*par)["Time"] = 99;
	}
	
	entities = new Entity*[entityCount];

	for (int i = 0; i < entityCount - 1; i++)
	{
		entities[i] = new Enemy();
		entities[i]->init(gameMap, enums::TileType::Enemy);
	}
	entities[entityCount - 1] = new Enemy();
	entities[entityCount - 1]->init(gameMap, enums::TileType::EnemySide);
	player = new Player(par);
	player->init(gameMap, enums::TileType::PlayerSide);

	int frameT[9] = { 60, 55, 50, 40, 30, 25, 20, 17, 15 };
	frameTime = frameT[skill - 1];
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
	auto static gameTime = SDL_GetTicks();
	static unsigned slowCounter = 1;

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
				return nullptr;
			}
		}
		BonusManager::getManager().update();
		time = SDL_GetTicks();
	}

	if (gameTime + 1000 < SDL_GetTicks())
	{
		unsigned lastedTime = (*par)["Time"]--;
		if (lastedTime == 0)
		{
			delete this;
			return nullptr;
		}
		gameTime = SDL_GetTicks();
	}

	return this;
}

void GameField::render(SDL_Renderer* renderer)
{
	static SDL_Rect dstRect = { 0, 0, 18, 18 };
	static int screenY = Config::getConfig().windowHeight;
	static int screenX = Config::getConfig().windowWidth;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((int)gameMap[i][j] < 7)
				SDL_RenderCopy(renderer, ResourceManager::getManager().mainSprites[(int)gameMap[i][j]], nullptr, &dstRect);
			dstRect.x += 18;
		}
		dstRect.x = 0;
		dstRect.y += 18;
	}
	dstRect.x = 0;
	dstRect.y = 0;
	BonusManager::getManager().render(renderer);
	GraphicManager::clearTray();
	GraphicManager::getManager().drawText(0, height * 18, 0xff, 0xff, 0xff, 32, "Score:");
	GraphicManager::getManager().drawText(142, height * 18, 0xff, 0xff, 0xff, 32, (*par)["Score"]);
	GraphicManager::getManager().drawText(screenX / 2 - 75, height * 18, 0xff, 0xff, 0xff, 32, "Time:");
	GraphicManager::getManager().drawText(screenX / 2 + 25, height * 18, 0xff, 0xff, 0xff, 32, (*par)["Time"]);
	GraphicManager::getManager().drawText(screenX - 130, height * 18, 0xff, 0xff, 0xff, 32, "Life:");
	GraphicManager::getManager().drawText(screenX - 30, height * 18, 0xff, 0xff, 0xff, 32, (*par)["Life"]);
}

bool GameField::init(SDL_Renderer* renderer)
{
	objRenderer = renderer;

	BonusManager::getManager().clear();
	BonusManager::getManager().setMap(gameMap);

	return true;
}

Scene* GameField::newLevel()
{
	auto _par = par;
	auto _skill = skill;
	if (_skill >= 9)
	{
		delete this;
		return nullptr;
	}
	delete this;
	return new GameField(_par, _skill + 1);
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
	float area = (counter / S);
	return area > 0.8;
}
