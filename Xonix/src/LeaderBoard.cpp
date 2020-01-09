#include "../include/LeaderBoard.h"

int cmp(const void* a, const void* b)
{
	const std::pair<std::string, int>* lhs = static_cast<const std::pair<std::string, int>*>(a);
	const std::pair<std::string, int>* rhs = static_cast<const std::pair<std::string, int>*>(b);

	if (lhs->second < rhs->second) return 1;
	else if (lhs->second > rhs->second) return -1;
	else return 0;
};

LeaderBoard::LeaderBoard(Scene* _mainMenu, SDL_Renderer* _objRenderer)
{
	mainMenu = _mainMenu;
	objRenderer = _objRenderer;
	lbFile.open("data/LeaderBoard.lb");
	if (lbFile.is_open() == false)
		std::cout << "Can't open the LeaderBoard file" << std::endl;
	for (int i = 0; i < lbCount; i++)
	{
		if (lbFile.good() == false)
			break;
		std::string name;
		int score;
		lbFile >> name;
		lbFile >> score;
		lb[i].first = name;
		lb[i].second = score;
	}

	lbFile.close();

	btn = new Button(Config::getConfig().windowWidth / 2 - buttonWidth / 2, Config::getConfig().windowWidth / 2 + buttonHeight / 2, buttonWidth, buttonHeight);

	btn->getEvent() = enums::GameEvent::Quit;
	btn->getString().assign(u8"Íàçàä");

	btn->isVisible() = true;
	btn->init(objRenderer);
	buttonStartX = btn->getX();
	buttonStartY = btn->getY();
	buttonEndX = btn->getX() + buttonWidth;
	buttonEndY = btn->getY() + buttonHeight;
}

LeaderBoard::LeaderBoard(int _score, std::string _name, SDL_Renderer* _objRenderer) : mainMenu(nullptr)
{
	lbFile.open("data/LeaderBoard.lb");
	if (lbFile.is_open() == false)
		std::cout << "Can't open the LeaderBoard file" << std::endl;

	objRenderer = _objRenderer;

	for (int i = 0; i < lbCount; i++)
	{
		if (lbFile.good() == false)
			break;
		std::string name;
		int score;
		lbFile >> name;
		lbFile >> score;
		lb[i].first = name;
		lb[i].second = score;
	}

	std::qsort(lb, lbCount, sizeof(std::pair<std::string, int>), cmp);

	if (lb[0].first == "")
	{
		lb[0].first = _name;
		lb[0].second = _score;
	}
	else
	{
		for (int i = 0; i < lbCount; i++)
		{
			if (lb[i].second <= _score)
			{
				memcpy(&(lb[i + 1]), &(lb[i]), sizeof(std::pair<std::string, int>) * (lbCount - 1 - i));
				lb[i].first = _name;
				lb[i].second = _score;
				break;
			}
		}
	}


	lbFile.close();

	btn = new Button(Config::getConfig().windowWidth / 2 - buttonWidth / 2, Config::getConfig().windowWidth / 2 + buttonHeight / 2, buttonWidth, buttonHeight);

	btn->getEvent() = enums::GameEvent::Quit;
	btn->getString().assign(u8"Âûõîä");

	btn->isVisible() = true;
	btn->init(objRenderer);
	buttonStartX = btn->getX();
	buttonStartY = btn->getY();
	buttonEndX = btn->getX() + buttonWidth;
	buttonEndY = btn->getY() + buttonHeight;
}

LeaderBoard::~LeaderBoard()
{
	delete btn;
}

Scene* LeaderBoard::handleEvent(const enums::GameEvent& event)
{
	static int x = 0, y = 0;
	if (event == enums::GameEvent::MouseButtonPressed)
	{
		SDL_GetMouseState(&x, &y);
		if ((y >= buttonStartY && y <= buttonEndY) && (x >= buttonStartX && x <= buttonEndX))
		{
			lbFile.open("data/LeaderBoard.lb", std::ios_base::out | std::ios_base::trunc);
			if (lbFile.is_open() == false)
				std::cout << "Can't open the LeaderBoard file" << std::endl;

			for (int i = 0; i < lbCount && lb[i].first != ""; i++)
				lbFile << lb[i].first << " " << lb[i].second << '\n';

			lbFile.close();

			auto temp = mainMenu;
			delete this;
			return temp;
		}
	}
	else
	{
		if (event == enums::GameEvent::Quit)
		{
			lbFile.open("data/LeaderBoard.lb", std::ios_base::out | std::ios_base::trunc);
			if (lbFile.is_open() == false)
				std::cout << "Can't open the LeaderBoard file" << std::endl;

			for (int i = 0; i < lbCount; i++)
				lbFile << lb[i].first << " " << lb[i].second << '\n';

			lbFile.close();

			auto temp = mainMenu;
			delete this;
			return temp;
		}
	}

	return this;
}

Scene* LeaderBoard::update()
{
	return this;
}

void LeaderBoard::render(SDL_Renderer* renderer)
{
	static int titleOffsetX = Config::getConfig().windowWidth / 2 - 615;

	GraphicManager::clearScreen();
	GraphicManager::drawText(titleOffsetX, 30, 86, 94, 255, 108, u8"ÒÀÁËÈÖÀ ËÈÄÅÐÎÂ");
	for (int i = 0; i < 15; i++)
	{
		if (lb[i].first == "")
			break;
		GraphicManager::drawText(titleOffsetX, 170 + i * 32, 255, 255, 255, 32,std::to_string(i + 1).append("."));
		GraphicManager::drawText(titleOffsetX + 80, 170 + i * 32, 255, 255, 255, 32, lb[i].first);
		GraphicManager::drawText(Config::getConfig().windowWidth - titleOffsetX - 150, 170 + i * 32, 255, 255, 255, 32, lb[i].second);
	}
	btn->render();
}

bool LeaderBoard::init(SDL_Renderer* renderer)
{
	return true;
}
