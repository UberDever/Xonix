#pragma once

#include "Enums.h"

constexpr unsigned BONUS_COUNT = 10;

class Bonus
{
private:
	enums::Bonus type;
	unsigned lifeTime;
	unsigned actTime;

public:
	Bonus(): type(enums::Bonus::Void), lifeTime(0), actTime(0) {}
	void init(enums::Bonus _type, unsigned _lifeTime, unsigned _actTime) { type = _type; lifeTime = _lifeTime; actTime = _actTime; }
};

class BonusManager
{
private:
	Bonus* bonusTypes;
	Bonus bonusOnScreen[BONUS_COUNT];
	enums::TileType** gameMap;

	BonusManager(const BonusManager&) = delete;
	BonusManager& operator=(BonusManager&) = delete;

	BonusManager() : bonusTypes(nullptr), gameMap(nullptr) {};
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

	void init(enums::TileType** _gameMap);
	void update();

};