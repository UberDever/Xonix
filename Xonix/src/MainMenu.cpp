#include "../include/MainMenu.h"

MainMenu::MainMenu() : objRenderer(nullptr), buttons{ nullptr }
{
	for (int i = 0; i < maxButtons; i++)
	{
		buttons[i] = new Button((Config::getConfig().windowWidth / 2) - (buttonWidth / 2),
			(Config::getConfig().windowHeight / 2) - maxButtons * buttonHeight / 2 + (120 * i), buttonWidth, buttonHeight);
	}

	buttons[maxButtons - 1]->getEvent() = enums::GameEvent::Quit;
	buttons[0]->getEvent() = enums::GameEvent::Start;
	buttons[1]->getEvent() = enums::GameEvent::Options;
	buttons[2]->getEvent() = enums::GameEvent::LeaderBoard;

	buttons[0]->getString().assign(u8"Начать игру");
	buttons[1]->getString().assign(u8"Настройки");
	buttons[2]->getString().assign(u8"Таблица рекордов");
	buttons[3]->getString().assign(u8"Выход");

	buttonStartX = buttons[0]->getX();
	buttonStartY = buttons[0]->getY();
	buttonEndX = buttons[maxButtons - 1]->getX() + buttonWidth;
	buttonEndY = buttons[maxButtons - 1]->getY() + buttonHeight;

	gameField = new GameField();
}

MainMenu::~MainMenu()
{
	for (int i = 0; i < maxButtons; i++)
	{
		delete buttons[i];
	}
}

Scene* MainMenu::handleEvent(const enums::GameEvent& event)
{
	int y_i = 0;

	if (event == enums::GameEvent::MouseButtonPressed)
	{
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		if ((y >= buttonStartY && y <= buttonEndY) && (x >= buttonStartX && x <= buttonEndX))
		{
			y -= buttonStartY;
			x -= buttonStartX;
			y_i = (y / (buttonHeight + offset)) + 1;
			if ((y_i * (buttonHeight + offset)) - y >= offset)
			{
				switch (buttons[y_i - 1]->getEvent())
				{
				case enums::GameEvent::Start:
				{
					break;
				}
				case enums::GameEvent::Quit:
				{
					delete this;
					return nullptr;
				}
				default:
					break;
				}
			}
		}
	}
	
	return this;
}

Scene* MainMenu::update()
{
	gameField->update();
	return this;
}

void MainMenu::render(SDL_Renderer* renderer)
{
	gameField->render(renderer);
	for (int i = 0; i < maxButtons; i++)
		buttons[i]->render();
	SDL_RenderPresent(objRenderer);
}

bool MainMenu::init(SDL_Window* window)
{
	for (int i = 0; i < maxButtons; i++)
		if (!buttons[i]->init(window))
			return false;

	objRenderer = SDL_GetRenderer(window);
	if (objRenderer == nullptr)
		return false;

	if (!gameField->init(window))
		return false;
	return true;
}
