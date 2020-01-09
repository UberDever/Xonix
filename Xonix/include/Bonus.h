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
public:
	struct POS
	{
		int x, y;
		POS() : x(0), y(0) {};
	} pos;

	enums::Bonus type;
	unsigned lifeTime;

	enums::TileType** gameMap;

public:

	Bonus() : type(enums::Bonus::Void), lifeTime(0), gameMap(nullptr) {}
	Bonus(int x, int y) : type(enums::Bonus::Void), lifeTime(0), gameMap(nullptr) { pos.x = x; pos.y = y; }
	void init(enums::Bonus _type, unsigned _lifeTime) { type = _type; lifeTime = _lifeTime;}
	void render(SDL_Renderer*);
	bool isActive() { return type != enums::Bonus::Void; }

	unsigned clock()
	{
		if (lifeTime > 0)
		{
			lifeTime--;
		}
		return lifeTime;
	}

	void genPos()
	{
		do {
			pos.x = rand() % ((int)(Config::getConfig().windowWidth / 18) - 4) + 2;
			pos.y = rand() % ((int)(Config::getConfig().windowHeight / 18) - 4) + 2;
		} while (gameMap[pos.y][pos.x] != enums::TileType::Void && gameMap[pos.y][pos.x] != enums::TileType::Wall);
		gameMap[pos.y][pos.x] = gameMap[pos.y][pos.x] == enums::TileType::Void ? enums::TileType::BonusVoid : enums::TileType::BonusWall;
	}

	void clear()
	{
		type = enums::Bonus::Void;
		lifeTime = 0;
		if (gameMap[pos.y][pos.x] == enums::TileType::BonusVoid)
			gameMap[pos.y][pos.x] = enums::TileType::Void;
		else if (gameMap[pos.y][pos.x] == enums::TileType::BonusWall)
			gameMap[pos.y][pos.x] = enums::TileType::Wall;
	}

	void apply(std::unordered_map<std::string, unsigned int>* par)
	{
		if (type == enums::Bonus::Random)
		{
			type = (enums::Bonus)(rand() % 5 + 1);
		}
		switch (type)
		{
		case enums::Bonus::Life:
			(*par)["Life"]++;
			break;
		case enums::Bonus::Time:
			(*par)["Time"] = 99;
			break;
		case enums::Bonus::Score:
			(*par)["Score"] += 1000;
			break;
		case enums::Bonus::Acceleration:
			(*par)["Acceleration"] = 2;
			break;
		case enums::Bonus::Slow:
			(*par)["Slow"] = 2;
			break;
		default:
			std::cout << "Bonus apply error" << std::endl;
			break;
		}
	}

	enums::TileType**& getMap() { return gameMap; }

	Bonus& operator= (const Bonus& rhs)
	{
		this->type = rhs.type;
		this->lifeTime = rhs.lifeTime;
		return *this;
	}

	inline bool operator== (const Bonus& rhs) const
	{
		return (this->pos.x == rhs.pos.x) && (this->pos.y == rhs.pos.y);
	}
};

class BonusManager
{
private:
	Bonus* bonusTypes;
	std::list<Bonus> bonusOnScreen;
	static unsigned activeBonuses;
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
	void setMap(enums::TileType**);
	Bonus pickBonus(int x, int y);
	void clear()
	{ 
		bonusOnScreen.clear();
		bonusOnScreen.resize(BONUS_COUNT);
		activeBonuses = 0;
	}
};

