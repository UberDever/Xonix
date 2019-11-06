#include "../include/Entity.h"

void Enemy::BFS()
{

}

void Enemy::init(enums::TileType** _gameMap, enums::TileType _type)
{
	gameMap = _gameMap;
	type = _type;
	vec.x = vec.y = 1;
	if (type == enums::TileType::Enemy)
	{
		pos.x = rand() % ((int)(Config::getConfig().windowWidth / 18) - 4) + 2;
		pos.y = rand() % ((int)(Config::getConfig().windowHeight / 18) - 4) + 2;
	}
	if (rand() % 255 > 127) { vec.x *= -1; }
	if (rand() % 255 > 127) { vec.y *= -1; }
	gameMap[pos.y][pos.x] = type;
}

void Enemy::handleEvent(const enums::GameEvent& event)
{

}


Entity* Enemy::update()
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
	return this;
}

/*****************************************************************************************************************************/

constexpr int GAME_PARAMETERS = 5;

Player::Player() : Entity()
{
	par.reserve(GAME_PARAMETERS);
	std::string names[] = {"Life", "Time", "Score", "Acceleration", "Slow"};
	unsigned values[] = { 3, 100, 0, 1, 1 };
	for (int i = 0; i < GAME_PARAMETERS; i++)
	{
		par[names[i]] = values[i];
	}
}

void Player::init(enums::TileType** _gameMap, enums::TileType _type)
{
	gameMap = _gameMap;
	type = _type;
	pos.y = 0;
	pos.x = Config::getConfig().windowWidth / 18 / 2;
	gameMap[pos.y][pos.x] = type;
}

void Player::handleEvent(const enums::GameEvent& event)
{
	switch (event)
	{
	case enums::GameEvent::Up:
	{
		vec.x = 0; vec.y = -1;
		break;
	}
	case enums::GameEvent::Down:
	{
		vec.x = 0; vec.y = 1;
		break;
	}
	case enums::GameEvent::Left:
	{
		vec.x = -1; vec.y = 0;
		break;
	}
	case enums::GameEvent::Right:
	{
		vec.x = 1; vec.y = 0;
		break;
	}
	default:
	{
		break;
	}
	}
}

Player* Player::update()
{
	static enums::TileType floor = enums::TileType::Wall;
	static int borderY = Config::getConfig().windowHeight / 18;
	static int borderX = Config::getConfig().windowWidth / 18;
	if (!((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0) && (pos.x + vec.x < borderX) && (pos.x + vec.x >= 0)))
	{
		vec.x = vec.y = 0;
	}
	if (gameMap[pos.y + vec.y][pos.x + vec.x] == enums::TileType::PlayerTrail)
	{
		delete this;
		return nullptr;
	}
	gameMap[pos.y][pos.x] = floor == enums::TileType::Wall ? floor : enums::TileType::PlayerTrail;
	pos.y += vec.y;
	pos.x += vec.x;
	floor = gameMap[pos.y][pos.x];
	type = floor == enums::TileType::Void ? enums::TileType::PlayerVoid : enums::TileType::PlayerSide;
	gameMap[pos.y][pos.x] = type;
	return this;
}
