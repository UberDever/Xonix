#include "..\include\Bonus.h"

void Bonus::render(SDL_Renderer* renderer)
{
	SDL_Rect dstRect = { pos.x * 18, pos.y * 18, 18, 18 };
	SDL_RenderCopy(renderer, ResourceManager::getManager().sprites[3], nullptr, &dstRect);
}

/******************************************************************************************************************************/

void BonusManager::init()
{
	bonusTypes = new Bonus[7];
	constexpr int typesCount = 7;
	enums::Bonus types[typesCount] = { enums::Bonus::Time, enums::Bonus::Life, enums::Bonus::Score,
		enums::Bonus::Acceleration, enums::Bonus::Slow, enums::Bonus::Random, enums::Bonus::Void };
	unsigned lifeTimes[typesCount] = { 30, 30, 30, 30, 30, 30, 0 };
	unsigned actTimes[typesCount] = { 30, 30, 30, 30, 30, 30, 0 };
	for (int i = 0; i < typesCount; i++)
	{
		bonusTypes[i].init(types[i], lifeTimes[i], actTimes[i]);
	}
}

void BonusManager::update()
{
	auto static time = SDL_GetTicks();
	int static cooldown = 1000;
	if (time + cooldown < SDL_GetTicks())
	{
		if ((rand() % 100) < 110)
		{
			if (bonusOnScreen.size() < BONUS_COUNT)
			{
				int randType = rand() % 6;
				bonusOnScreen.insert(bonusOnScreen.begin(), bonusTypes[randType]);
				bonusOnScreen.front().genPos(gameMap);
			}
		}
		for (auto it = bonusOnScreen.begin(); it != bonusOnScreen.end(); it++)
		{
			if (it->clock() == 0)
			{
				it = bonusOnScreen.erase(it);
				it--;
			}
		}
		time = SDL_GetTicks();
	}
	
}

void BonusManager::render(SDL_Renderer* renderer)
{
	for (auto it = bonusOnScreen.begin(); it != bonusOnScreen.end(); it++)
	{
		it->render(renderer);
	}
}

enums::TileType**& BonusManager::getMap()
{
	return gameMap;
}
