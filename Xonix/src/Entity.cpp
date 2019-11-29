#include "../include/Entity.h"

bool Entity::isPlayerAlive = true;

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
	enums::TileType curFloor = (type == enums::TileType::EnemySide) ? enums::TileType::Wall : enums::TileType::Void;
	static int borderY = Config::getConfig().windowHeight / 18;
	static int borderX = Config::getConfig().windowWidth / 18;
	bool isCollision = false;
	VECT oldVec = vec;
	if ((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0) && (pos.x + vec.x < borderX) && (pos.x + vec.x >= 0))
	{
		if (gameMap[pos.y + vec.y][pos.x] != curFloor) { vec.y *= -1; isCollision = true; }
		if (gameMap[pos.y][pos.x + vec.x] != curFloor) { vec.x *= -1; isCollision = true; }
		if (gameMap[pos.y + vec.y][pos.x + vec.x] != curFloor) { vec.x *= -1; vec.y *= -1; isCollision = true; }
	}
	else
	{
		if (!((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0))) { vec.y *= -1; }
		if (!((pos.x + vec.x < borderX) && (pos.x + vec.x >= 0))) { vec.x *= -1; }
		//oldVec.x = oldVec.y = 0;
	}
	if (isCollision == true)
	{
		if ((gameMap[pos.y + oldVec.y][pos.x + oldVec.x] >= enums::TileType::PlayerSide) &&
			(gameMap[pos.y + oldVec.y][pos.x + oldVec.x] <= enums::TileType::PlayerTrail))
		{
			isPlayerAlive = false;
		}
	}
	gameMap[pos.y][pos.x] = curFloor;
	pos.y += vec.y;
	pos.x += vec.x;
	gameMap[pos.y][pos.x] = type;
	return this;
}

/*****************************************************************************************************************************/

Player::Player(std::unordered_map<std::string, unsigned int>* _par) : Entity(), par(nullptr)
{
	par = _par;
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
	if (gameMap[pos.y + vec.y][pos.x + vec.x] == enums::TileType::PlayerTrail || isPlayerAlive == false)
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
