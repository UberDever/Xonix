#include "../include/Entity.h"

bool Entity::isPlayerAlive = true;
bool Entity::isPathCompleted = false;

int Entity::borderX = Config::getConfig().windowWidth / 18;
int Entity::borderY = Config::getConfig().windowHeight / 18;

inline void Enemy::BFS()
{
	if (isPathCompleted == true)
	{
		if (type == enums::TileType::Enemy)
		{
			_bfs({ pos.x, pos.y });
		}
		else
		{
			isPathCompleted = false;
			for (int i = 0; i < borderY; i++)
			{
				for (int j = 0; j < borderX; j++)
				{
					switch (gameMap[i][j])
					{
					case enums::TileType::Marked:
						gameMap[i][j] = enums::TileType::Void;
						break;
					case enums::TileType::BonusMarked:
						gameMap[i][j] = enums::TileType::BonusVoid;
						break;
					case enums::TileType::BonusVoid:
						gameMap[i][j] = enums::TileType::BonusWall;
						break;
					case enums::TileType::Enemy:
						gameMap[i][j] = enums::TileType::Enemy;
						break;
					case enums::TileType::BonusWall:
						gameMap[i][j] = enums::TileType::BonusWall;
						break;
					case enums::TileType::EnemySide:
						gameMap[i][j] = enums::TileType::EnemySide;
						break;
					default:
						gameMap[i][j] = enums::TileType::Wall;
						break;
					}
				}
			}
		}
	}
}

void Enemy::_bfs(POS entry)
{
	if (gameMap[entry.y][entry.x] == enums::TileType::BonusVoid) gameMap[entry.y][entry.x] = enums::TileType::BonusMarked;
	if (gameMap[entry.y][entry.x] == enums::TileType::Void)
	{
		gameMap[entry.y][entry.x] = enums::TileType::Marked;
		_bfs({ entry.x - 1, entry.y });
		_bfs({ entry.x, entry.y + 1 });
		_bfs({ entry.x + 1, entry.y });
		_bfs({ entry.x, entry.y - 1 });
	}
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
	bool isCollision = false;
	VECT oldVec = vec;
	if ((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0) && (pos.x + vec.x < borderX) && (pos.x + vec.x >= 0))
	{
		if (gameMap[pos.y + vec.y][pos.x] != curFloor) { vec.y *= -1; isCollision = true; }
		if (gameMap[pos.y][pos.x + vec.x] != curFloor) { vec.x *= -1; isCollision = true; }
		if (gameMap[pos.y + vec.y][pos.x + vec.x] != curFloor) { vec.x = -oldVec.x; vec.y = -oldVec.y; isCollision = true; }
	}
	else
	{
		if (!((pos.y + vec.y < borderY) && (pos.y + vec.y >= 0))) { vec.y *= -1; }
		if (!((pos.x + vec.x < borderX) && (pos.x + vec.x >= 0))) { vec.x *= -1; }
	}
	if (isCollision == true)
	{
		if ((gameMap[pos.y + oldVec.y][pos.x + oldVec.x] == enums::TileType::PlayerSide) ||
			(gameMap[pos.y + oldVec.y][pos.x + oldVec.x] == enums::TileType::PlayerVoid) ||
			(gameMap[pos.y + oldVec.y][pos.x + oldVec.x] == enums::TileType::PlayerTrail))
		{
			isPlayerAlive = false;
		}
	}
	gameMap[pos.y][pos.x] = curFloor;
	BFS();
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
	if (gameMap[pos.y + vec.y][pos.x + vec.x] == enums::TileType::PlayerTrail ||
		gameMap[pos.y + vec.y][pos.x + vec.x] == enums::TileType::Enemy ||
		gameMap[pos.y + vec.y][pos.x + vec.x] == enums::TileType::EnemySide ||
		isPlayerAlive == false)
	{
		if ((*par)["Life"] != 0)
		{
			(*par)["Life"]--;
			isPlayerAlive = true;
			gameMap[pos.y][pos.x] = floor;
			floor = enums::TileType::Wall;
			pos.y = 0;
			pos.x = Config::getConfig().windowWidth / 18 / 2;
			vec.x = 0;
			vec.y = 0;
			for (int i = 0; i < borderY; i++)
			{
				for (int j = 0; j < borderX; j++)
				{
					if (gameMap[i][j] == enums::TileType::PlayerTrail)
						gameMap[i][j] = enums::TileType::Void;
				}
			}
		}
		else
		{
			delete this;
			return nullptr;
		}
	}
	gameMap[pos.y][pos.x] = floor == enums::TileType::Wall ? floor : enums::TileType::PlayerTrail;
	pos.y += vec.y;
	pos.x += vec.x;
	if (gameMap[pos.y][pos.x] == enums::TileType::BonusVoid || gameMap[pos.y][pos.x] == enums::TileType::BonusWall)
	{
		Bonus bonus = BonusManager::getManager().pickBonus(pos.x, pos.y);
		bonus.apply(par);
	}
	if ((gameMap[pos.y - vec.y][pos.x - vec.x] == enums::TileType::PlayerTrail) && 
		(gameMap[pos.y][pos.x] == enums::TileType::Wall))
		isPathCompleted = true;
	floor = gameMap[pos.y][pos.x];
	type = floor == enums::TileType::Void ? enums::TileType::PlayerVoid : enums::TileType::PlayerSide;
	gameMap[pos.y][pos.x] = type;
	return this;
}
