#include "..\include\Bonus.h"

void BonusManager::init(enums::TileType** _gameMap)
{
	gameMap = _gameMap;
	bonusTypes = new Bonus();
	constexpr int typesCount = 6;
	enums::Bonus types[typesCount] = { enums::Bonus::Time, enums::Bonus::Life, enums::Bonus::Score, enums::Bonus::Acceleration, enums::Bonus::Slow, enums::Bonus::Random };
	unsigned lifeTimes[typesCount] = { 30, 30, 30, 30, 30, 30 };
	unsigned actTimes[typesCount] = { 30, 30, 30, 30, 30, 30 };
	for (int i = 0; i < typesCount; i++)
	{
		bonusTypes->init(types[i], lifeTimes[i], actTimes[i]);
	}
}

void BonusManager::update()
{

}
