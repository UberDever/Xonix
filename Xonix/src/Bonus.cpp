#include "..\include\Bonus.h"

void Bonus::render(SDL_Renderer* renderer)
{
	SDL_Rect dstRect = { pos.x * 18, pos.y * 18, 18, 18 };
	SDL_RenderCopy(renderer, ResourceManager::getManager().bonusSprites[(int)type], nullptr, &dstRect);
}

/******************************************************************************************************************************/

unsigned BonusManager::activeBonuses = 0;

void BonusManager::init()
{
	bonusTypes = new Bonus[7];
	constexpr int typesCount = 7;
	enums::Bonus types[typesCount] = { enums::Bonus::Time, enums::Bonus::Life, enums::Bonus::Score,
		enums::Bonus::Acceleration, enums::Bonus::Slow, enums::Bonus::Random, enums::Bonus::Void };
	unsigned lifeTimes[typesCount] = { 10, 10, 10, 10, 10, 10, 0 };
	for (int i = 0; i < typesCount; i++)
	{
		bonusTypes[i].init(types[i], lifeTimes[i]);
	}

	bonusOnScreen.resize(BONUS_COUNT);
}

void BonusManager::update()
{
	auto static time = SDL_GetTicks();
	int static cooldown = 200;
	if (time + cooldown < SDL_GetTicks())
	{
		if ((rand() % 100) < 110)
		{
			if (activeBonuses < BONUS_COUNT)
			{
				int randType = rand() % 6;
				for (auto& it : bonusOnScreen)
				{
					if (it.isActive() == false)
					{
						it = bonusTypes[randType];
						it.genPos();
						activeBonuses++;
						break;
					}
				}
			}
		}
		for (auto& it : bonusOnScreen)
		{
			if (it.isActive() == false)
				break;

			if (it.clock() == 0)
			{
				it.clear();
				activeBonuses--;
			}
		}
		time = SDL_GetTicks();
	}
	
}

void BonusManager::render(SDL_Renderer* renderer)
{
	for (auto& it : bonusOnScreen)
	{
		if (it.isActive())
			it.render(renderer);
	}
}

void BonusManager::setMap(enums::TileType** _gameMap)
{
	gameMap = _gameMap;
	for (auto& it : bonusOnScreen)
	{
		it.getMap() = _gameMap;
	}
}

Bonus BonusManager::pickBonus(int x, int y)
{
	Bonus temp = Bonus(x, y);
	auto it = std::find(bonusOnScreen.begin(), bonusOnScreen.end(), temp);
	auto bonus = *it;
	it->clear();
	activeBonuses--;
	return bonus;
}
