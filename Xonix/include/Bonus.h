#pragma once

#include <iostream>
#include <list>
#include <SDL.h>
#include "Enums.h"
#include "Config.h"
#include "ResourceManager.h"

constexpr unsigned BONUS_COUNT = 10;

class Bonus
{
private:
	struct POS
	{
		int x, y;
		POS() : x(0), y(0) {};
	} pos;

	enums::Bonus type;
	unsigned lifeTime;
	unsigned actTime;

public:
	Bonus(): type(enums::Bonus::Void), lifeTime(0), actTime(0) {}
	void init(enums::Bonus _type, unsigned _lifeTime, unsigned _actTime) { type = _type; lifeTime = _lifeTime; actTime = _actTime; }
	void render(SDL_Renderer*);
	bool isActive() { return type != enums::Bonus::Void; }

	int clock()
	{
		if (lifeTime > 0)
		{
			lifeTime--;
		}
		return lifeTime;
	}

	void genPos(enums::TileType**& gameMap)
	{
		pos.x = rand() % ((int)(Config::getConfig().windowWidth / 18) - 4) + 2;
		pos.y = rand() % ((int)(Config::getConfig().windowHeight / 18) - 4) + 2;
		gameMap[pos.y][pos.x] = enums::TileType::Bonus;
	}

	Bonus& operator= (const Bonus& rhs)
	{
		this->pos.x = rhs.pos.x;
		this->pos.y = rhs.pos.y;
		this->type = rhs.type;
		this->actTime = rhs.actTime;
		this->lifeTime = rhs.lifeTime;
		return *this;
	}
};

class BonusManager
{
private:
	Bonus* bonusTypes;
	std::list<Bonus> bonusOnScreen;
	enums::TileType** gameMap;

	BonusManager(const BonusManager&) = delete;
	BonusManager& operator=(BonusManager&) = delete;

	BonusManager(): bonusTypes(nullptr), gameMap(nullptr) {};
	~BonusManager()
	{
		delete bonusTypes;
	};

public:

	static BonusManager& getManager()
	{
		static BonusManager instance;
		return instance;
	}

	void init();
	void update();
	void render(SDL_Renderer*);
	enums::TileType**& getMap();
};

