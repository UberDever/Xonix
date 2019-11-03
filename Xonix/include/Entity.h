#pragma once
#include <iostream>
#include <SDL.h>
#include "Config.h"
#include "Enums.h"

class Entity
{
protected:
	struct POS
	{
		int x, y;
		POS() : x(0), y(1) {}
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

public:

	Enemy() : Entity() {};

	void init(enums::TileType** _gameMap, enums::TileType _type) override;
	void handleEvent(const enums::GameEvent& event) override;
	Entity* update() override;
};

class Player : public Entity
{
private:


public:

	Player() : Entity() {};

	void init(enums::TileType** _gameMap, enums::TileType _type) override;
	void handleEvent(const enums::GameEvent& event);
	Entity* update() override;
};

