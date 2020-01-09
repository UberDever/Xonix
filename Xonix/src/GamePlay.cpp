#include "../include/GamePlay.h"

GamePlay::GamePlay(std::string _name, Scene* _gameField, SDL_Renderer* rend)
{
	name = _name;
	gameField = _gameField;
	gameField->init(nullptr);
	objRenderer = rend;
}

GamePlay::~GamePlay()
{
	delete gameField;
}

Scene* GamePlay::handleEvent(const enums::GameEvent& event)
{
	switch (event)
	{
	case enums::GameEvent::Quit:
	{
		return new Pause(this, objRenderer);
		break;
	}
	default:
	{
		gameField = gameField->handleEvent(event);
		break;
	}
	}
	return this;
}

Scene* GamePlay::update()
{
	score = static_cast<GameField*>(gameField)->querryScore();
	gameField = gameField->update();
	if (gameField == nullptr)
	{
		auto _score = score;
		auto _name = name;
		auto _objRenderer = objRenderer;
		delete this;
		return new LeaderBoard(_score, _name, _objRenderer);
	}
	else if (static_cast<GameField*>(gameField)->isFilled())
	{
		gameField = static_cast<GameField*>(gameField)->newLevel();
		if (gameField == nullptr)
		{
			auto _score = score + 135000;
			auto _name = name;
			auto _objRenderer = objRenderer;
			delete this;
			return new LeaderBoard(_score, _name, _objRenderer);
		}
		gameField->init(nullptr);
	}
	return this;
}

void GamePlay::render(SDL_Renderer* renderer)
{
	gameField->render(renderer);
}

/**********************************************************************************************************************************************/

Pause::Pause(Scene* gamePlay, SDL_Renderer* rend)
{
	pausedGame = gamePlay;
	for (int i = 0; i < 2; i++)
		buttons[i] = new Button(Config::getConfig().windowWidth / 2 - buttonWidth / 2, Config::getConfig().windowHeight / 2 - buttonHeight / 2 + (i * 120), buttonWidth, buttonHeight);
	
	objRenderer = rend;

	buttons[0]->getEvent() = enums::GameEvent::BeginGame;
	buttons[1]->getEvent() = enums::GameEvent::Quit;

	buttons[0]->getString().assign(u8"Продолжить");
	buttons[1]->getString().assign(u8"Выход");

	for (int i = 0; i < 2; i++)
		buttons[i]->isVisible() = true;

	for (int i = 0; i < 2; i++)
		buttons[i]->init(objRenderer);

	buttonStartX = buttons[0]->getX();
	buttonStartY = buttons[0]->getY();
	buttonEndX = buttons[1]->getX() + buttonWidth;
	buttonEndY = buttons[1]->getY() + buttonHeight;
}

Pause::~Pause()
{
	for (int i = 0; i < 2; i++)
		delete buttons[i];
}

Scene* Pause::handleEvent(const enums::GameEvent& event)
{
	static int x = 0, y = 0;
	static int y_i = 0;
	if (event == enums::GameEvent::MouseButtonPressed)
	{
		SDL_GetMouseState(&x, &y);
		if ((y >= buttonStartY && y <= buttonEndY) && (x >= buttonStartX && x <= buttonEndX))
		{
			y -= buttonStartY;
			x -= buttonStartX;
			y_i = y / (buttonHeight + offsetY);
			if (((y_i + 1) * (buttonHeight + offsetY)) - offsetY >= y)
			{
				switch (buttons[y_i]->getEvent())
				{
				case enums::GameEvent::BeginGame:
				{
					auto temp = pausedGame;
					delete this;
					return temp;
					break;
				}
				case enums::GameEvent::Quit:
				{
					Scene* temp = new MainMenu();
					temp->init(objRenderer);
					delete pausedGame;
					delete this;
					return temp;
					break;
				}
				default:
					break;
				}
			}
		}
	}
	else
	{
		if (event == enums::GameEvent::Quit)
		{
			auto temp = pausedGame;
			delete this;
			return temp;
		}
	}

	return this;
}

Scene* Pause::update()
{
	return this;
}

void Pause::render(SDL_Renderer* renderer)
{
	static int titleOffsetX = Config::getConfig().windowWidth / 2 - 210;

	GraphicManager::drawText(titleOffsetX, 50, 86, 94, 255, 108, u8"ПАУЗА");
	for (int i = 0; i < 2; i++)
		buttons[i]->render();
}

bool Pause::init(SDL_Renderer* renderer)
{
	return true;
}
