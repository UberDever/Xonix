#include "../include/Entity.h"

void Enemy::BFS()
{

}

void Enemy::init(enums::TileType** gameMapInstance, enums::TileType curType)
{
	gameMap = gameMapInstance;
	type = curType;
	if (type == enums::TileType::Enemy)
	{
		pos.x = rand() % ((int)(Config::getConfig().windowWidth / 18) - 4) + 2;
		pos.y = rand() % ((int)(Config::getConfig().windowHeight / 18) - 4) + 2;
	}
	if (rand() % 255 > 127) { vec.x *= -1; }
	if (rand() % 255 > 127) { vec.y *= -1; }
	gameMap[pos.y][pos.x] = type;
}


void Enemy::update()
{
	enums::TileType curWall = (type == enums::TileType::EnemySide) ? enums::TileType::Wall : enums::TileType::Void;
	static int borderY = Config::getConfig().windowHeight / 18;
	static int borderX = Config::getConfig().windowWidth / 18;
	gameMap[pos.y][pos.x] = curWall;
	if ((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0) && (pos.x + vec.x < borderX) && (pos.x + vec.x >= 0))
	{
		if (gameMap[pos.y + vec.y][pos.x] != curWall) { vec.y *= -1; }
		if (gameMap[pos.y][pos.x + vec.x] != curWall) { vec.x *= -1; }
	}
	else
	{
		if (!((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0)))
			vec.y *= -1;
		if (!((pos.x + vec.x < borderX) && (pos.x + vec.x >= 0)))
			vec.x *= -1;
		
	}
	pos.y += vec.y;
	pos.x += vec.x;
	gameMap[pos.y][pos.x] = type;
}
