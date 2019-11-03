#include "../include/MainMenu.h"

bool Button::init(SDL_Window* window)
{
	SDL_Surface* tempSurf = nullptr;
	SDL_Color color = { 255, 255, 255 };
	tempSurf = IMG_Load("data/sprites/button.png");
	tempSurf = SDL_ConvertSurfaceFormat(tempSurf, SDL_PIXELFORMAT_ARGB8888, 0);
	if (tempSurf == nullptr)
		return false;
	TTF_Font* font = nullptr;
	font = TTF_OpenFont("data/fonts/font.ttf", 32);
	if (font == nullptr)
		return false;
	SDL_Surface* tempText = nullptr;
	tempText = TTF_RenderUTF8_Blended(font, name.c_str(), color);
	if (tempText != nullptr)
	{
		SDL_Rect dstRect = { (this->w / 2 - tempText->w / 2), (this->h / 2 - tempText->h / 2), 0, 0 };
		SDL_BlitSurface(tempText, nullptr, tempSurf, &dstRect);
	}
	TTF_CloseFont(font);
	buttonTexture = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), tempSurf);
	SDL_FreeSurface(tempText);
	SDL_FreeSurface(tempSurf);
	if (buttonTexture == nullptr)
		return false;
	objRenderer = SDL_GetRenderer(window);
	if (objRenderer == nullptr)
		return false;
	return true;
}

MainMenu::MainMenu() : objRenderer(nullptr), buttons{ nullptr }
{
	for (int i = 0; i < mainScreenButtons; i++)
	{
		buttons[i] = new Button((Config::getConfig().windowWidth / 2) - (buttonWidth / 2),
			(Config::getConfig().windowHeight / 2) - mainScreenButtons * buttonHeight / 2 + (120 * i), buttonWidth, buttonHeight);
		buttons[i]->isVisible() = true;
	}

	for (int i = 0; i < (maxButtons - mainScreenButtons) / 2; i++)
	{
		buttons[i + mainScreenButtons] = new Button((Config::getConfig().windowWidth / 2) - (buttonWidth / 2) - ((offsetX + buttonWidth) / 2),
			(Config::getConfig().windowHeight / 2) - buttonsInColumn * buttonHeight / 2 + (120 * i), buttonWidth, buttonHeight);
		buttons[i + mainScreenButtons]->getEvent() = enums::GameEvent::Start;
	}

	for (int i = (maxButtons - mainScreenButtons) / 2; i < (maxButtons - mainScreenButtons); i++)
	{
		buttons[i + mainScreenButtons] = new Button((Config::getConfig().windowWidth / 2) - (buttonWidth / 2) + ((offsetX + buttonWidth) / 2),
			(Config::getConfig().windowHeight / 2) - buttonsInColumn * buttonHeight / 2 + (120 * (i - (maxButtons - mainScreenButtons) / 2)), buttonWidth, buttonHeight);
		buttons[i + mainScreenButtons]->getEvent() = enums::GameEvent::Start;
	}

	buttons[mainScreenButtons - 1]->getEvent() = enums::GameEvent::Quit;
	buttons[0]->getEvent() = enums::GameEvent::BeginGame;
	buttons[1]->getEvent() = enums::GameEvent::Options;
	buttons[2]->getEvent() = enums::GameEvent::LeaderBoard;

	buttons[maxButtons - 1]->getEvent() = enums::GameEvent::Quit;

	buttons[mainScreenButtons - 1]->getString().assign(u8"Выход");
	buttons[0]->getString().assign(u8"Начать игру");
	buttons[1]->getString().assign(u8"Настройки");
	buttons[2]->getString().assign(u8"Таблица рекордов");
	buttons[4]->getString().assign(u8"Замедленная");
	buttons[5]->getString().assign(u8"Небыстрая");
	buttons[6]->getString().assign(u8"Спокойная");
	buttons[7]->getString().assign(u8"Умеренная");
	buttons[8]->getString().assign(u8"Нормальная");
	buttons[9]->getString().assign(u8"Ускоренная");
	buttons[10]->getString().assign(u8"Стремительная");
	buttons[11]->getString().assign(u8"Сверхсветовая");
	buttons[12]->getString().assign(u8"Невозможная");
	buttons[13]->getString().assign(u8"Назад");

	buttonStartX = buttons[0]->getX();
	buttonStartY = buttons[0]->getY();
	buttonEndX = buttons[mainScreenButtons - 1]->getX() + buttonWidth;
	buttonEndY = buttons[mainScreenButtons - 1]->getY() + buttonHeight;

	gameField = new GameField(0);
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
	static int buttonOffset = 0;
	static int x = 0, y = 0;
	static int x_i = 0, y_i = 0;
	if (event == enums::GameEvent::MouseButtonPressed)
	{
		SDL_GetMouseState(&x, &y);
		if ((y >= buttonStartY && y <= buttonEndY) && (x >= buttonStartX && x <= buttonEndX))
		{
			y -= buttonStartY;
			x -= buttonStartX;
			y_i = y / (buttonHeight + offsetY);
			x_i = x / (buttonWidth + offsetX);
			if ((((y_i + 1) * (buttonHeight + offsetY)) - offsetY >= y) && (((x_i + 1) * (buttonWidth + offsetX)) - offsetX >= x))
			{
				switch (buttons[y_i + (x_i * buttonsInColumn) + buttonOffset]->getEvent())
				{
				case enums::GameEvent::BeginGame:
				{
					for (int i = 0; i < mainScreenButtons; i++) { buttons[i]->isVisible() = false; }
					for (int i = mainScreenButtons; i < maxButtons; i++) { buttons[i]->isVisible() = true; }
					buttonStartX = buttons[mainScreenButtons]->getX();
					buttonStartY = buttons[mainScreenButtons]->getY();
					buttonEndX = buttons[maxButtons - 1]->getX() + buttonWidth;
					buttonEndY = buttons[maxButtons - 1]->getY() + buttonHeight;
					buttonOffset = mainScreenButtons;
					break;
				}
				case enums::GameEvent::Start:
				{
					GamePlay* actualGame = new GamePlay(static_cast<Scene*>(new GameField(y_i + (x_i * buttonsInColumn) + 1)));
					delete this;
					return actualGame;
					break;
				}
				case enums::GameEvent::Quit:
				{
					if (buttonOffset == 0)
					{
						delete this;
						return nullptr;
					}
					else
					{
						for (int i = 0; i < mainScreenButtons; i++) { buttons[i]->isVisible() = true; }
						for (int i = mainScreenButtons; i < maxButtons; i++) { buttons[i]->isVisible() = false; }
						buttonStartX = buttons[0]->getX();
						buttonStartY = buttons[0]->getY();
						buttonEndX = buttons[mainScreenButtons - 1]->getX() + buttonWidth;
						buttonEndY = buttons[mainScreenButtons - 1]->getY() + buttonHeight;
						buttonOffset = 0;
					}
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
		if (event == enums::GameEvent::Quit && buttonOffset == 0)
		{
			delete this;
			return nullptr;
		}
	}
	
	return this;
}

Scene* MainMenu::update()
{
	gameField = gameField->update();
	if (gameField == nullptr)
	{
		delete this;
		return nullptr;
	}
	return this;
}

void MainMenu::render(SDL_Renderer* renderer)
{
	static int titleOffsetX = Config::getConfig().windowWidth / 2 - 210;

	gameField->render(renderer);
	for (int i = 0; i < maxButtons; i++)
	{
		if (buttons[i]->isVisible())
		{
			buttons[i]->render();
		}
	}
	GraphicManager::drawText(titleOffsetX, 50, 86, 94, 255, "XONIX");
}

bool MainMenu::init(SDL_Window* window)
{
	for (int i = 0; i < maxButtons; i++)
		if (!buttons[i]->init(window))
			return false;

	objRenderer = SDL_GetRenderer(window);
	if (objRenderer == nullptr)
		return false;

	ResourceManager::getManager().init(SDL_GetRenderer(window));
	GraphicManager::getManager().getRenderer() = SDL_GetRenderer(window);
	GraphicManager::getManager().getFont() = TTF_OpenFont("data/fonts/font.ttf", 108);

	if (!gameField->init(window))
		return false;
	return true;
}
