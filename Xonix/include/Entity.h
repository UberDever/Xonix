#pragma once
#include <iostream>
#include <SDL.h>
#include <unordered_map>
#include "Config.h"
#include "Enums.h"
#include "Bonus.h"

class Entity
{
protected:

	static bool isPlayerAlive;
	static bool isPathCompleted;

	static int borderY;
	static int borderX;

	struct POS
	{
		int x, y;
		POS() : x(0), y(1) {}
		POS(int _x, int _y) { x = _x; y = _y; }
	} pos;

	struct VECT
	{
		int x, y;
		VECT() : x(0), y(0) {}
	} vec;

	enums::TileType** gameMap;

	enums::TileType type;

public:
	Entity() : type(enums::TileType::Enemy), gameMap(nullptr) {};

	virtual void init(enums::TileType** _gameMap, enums::TileType _type) = 0;
	virtual void handleEvent(const enums::GameEvent& event) = 0;
	virtual Entity* update() = 0;
};

class Enemy : public Entity
{
private:

	void BFS();
	void _bfs(POS entry);

public:

	Enemy() : Entity() {};

	void init(enums::TileType** _gameMap, enums::TileType _type) override;
	void handleEvent(const enums::GameEvent& event) override;
	Entity* update() override;
};

class Player : public Entity
{
private:

	std::unordered_map<std::string, unsigned int>* par; //Life, Time, Score, AccelerationValue, SlowValue 

public:

	Player(std::unordered_map<std::string, unsigned int>* _par);

	void init(enums::TileType** _gameMap, enums::TileType _type) override;
	void handleEvent(const enums::GameEvent& event);
	Player* update() override;
};

//BONUSES:
//LIFE, TIME, SLOW, SCORE, ACCELERATION, RANDOM