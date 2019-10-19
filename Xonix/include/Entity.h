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

	enums::TileType type;

public:
	Entity() : type(enums::TileType::Enemy) {};

	virtual void init(enums::TileType**, enums::TileType _type) = 0;
	virtual void update() = 0;
};

class Enemy : public Entity
{
private:
	struct VECT
	{
		int x, y;
		VECT(): x(1), y(1) {}
	} vec;

	enums::TileType** gameMap;

	void BFS();

public:

	Enemy() : Entity(), gameMap(nullptr) {};

	void init(enums::TileType**, enums::TileType) override;
	void update() override;
};

