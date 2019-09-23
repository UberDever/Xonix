#include "../include/MainMenu.h"

MainMenu::MainMenu(): objRenderer(nullptr)
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		buttons[i] = new Button((globalConfig.windowWidth / 2) - (200 / 2),
			(globalConfig.windowHeight / 2) - (100 / 2) - 120 + (120 * i), 200, 100);
	}
}

MainMenu::~MainMenu()
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		delete buttons[i];
	}
}

Scene* MainMenu::handleEvent(const enums::GameEvent& event)
{
	switch (event)
	{
	case enums::GameEvent::MouseButtonPressed:
	{
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
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
	
	return this;
}

Scene* MainMenu::update(uint64_t delta)
{
	if (delta)
	std::cout << 1000000 / delta << std::endl;
	return this;
}

void MainMenu::render()
{
	for (int i = 0; i < MAX_BUTTONS; i++)
		buttons[i]->render();
	SDL_RenderPresent(objRenderer);
}

bool MainMenu::init(SDL_Window* window)
{
	for (int i = 0; i < MAX_BUTTONS; i++)
		if (!buttons[i]->init(window))

			return false;

	objRenderer = SDL_GetRenderer(window);
	if (objRenderer == nullptr)
		return false;
	return true;
}
