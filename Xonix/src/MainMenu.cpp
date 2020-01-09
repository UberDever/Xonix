#include "../include/MainMenu.h"

bool Button::init(SDL_Renderer* rend)
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
	buttonTexture = SDL_CreateTextureFromSurface(rend, tempSurf);
	SDL_FreeSurface(tempText);
	SDL_FreeSurface(tempSurf);
	if (buttonTexture == nullptr)
		return false;
	objRenderer = rend;
	if (objRenderer == nullptr)
		return false;
	return true;
}

MainMenu::MainMenu() : objRenderer(nullptr), buttons{ nullptr }, playerName("PLAYER_XONIX")
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
	buttons[1]->getString().assign(u8"Смена имени");
	buttons[2]->getString().assign(u8"Таблица рекордов");
	buttons[mainScreenButtons]->getString().assign(u8"Замедленная");
	buttons[mainScreenButtons + 1]->getString().assign(u8"Небыстрая");
	buttons[mainScreenButtons + 2]->getString().assign(u8"Спокойная");
	buttons[mainScreenButtons + 3]->getString().assign(u8"Умеренная");
	buttons[mainScreenButtons + 4]->getString().assign(u8"Нормальная");
	buttons[mainScreenButtons + 5]->getString().assign(u8"Ускоренная");
	buttons[mainScreenButtons + 6]->getString().assign(u8"Стремительная");
	buttons[mainScreenButtons + 7]->getString().assign(u8"Сверхсветовая");
	buttons[mainScreenButtons + 8]->getString().assign(u8"Невозможная");
	buttons[mainScreenButtons + 9]->getString().assign(u8"Назад");

	buttonStartX = buttons[0]->getX();
	buttonStartY = buttons[0]->getY();
	buttonEndX = buttons[mainScreenButtons - 1]->getX() + buttonWidth;
	buttonEndY = buttons[mainScreenButtons - 1]->getY() + buttonHeight;

	gameField = new GameField(nullptr, 0);
}

MainMenu::~MainMenu()
{
	for (int i = 0; i < maxButtons; i++)
	{
		delete buttons[i];
	}
	delete gameField;
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
					GamePlay* actualGame = new GamePlay(playerName, static_cast<Scene*>(new GameField(nullptr, y_i + (x_i * buttonsInColumn) + 1)), objRenderer);
					buttonOffset = 0;
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
				case enums::GameEvent::Options:
				{
					GraphicManager::clearScreen();
					GraphicManager::drawText(Config::getConfig().windowWidth / 2 - 210, 50, 86, 94, 255, 108, u8"ВВЕДИТЕ ИМЯ");
					SDL_RenderPresent(objRenderer);

					SDL_Event in_event;
					int len = 0;
					bool _running = true;
					std::string oldText = playerName;

					SDL_StartTextInput();
					while (_running) {
						SDL_Event event;
						if (SDL_PollEvent(&event)) {
							switch (event.type) {
							case SDL_KEYDOWN:
								if (event.key.keysym.sym == SDLK_ESCAPE)
								{
									playerName = oldText;
									_running = false;
								}
								else if (event.key.keysym.sym == SDLK_RETURN)
									_running = false;
								else if (event.key.keysym.sym == SDLK_BACKSPACE)
									playerName.pop_back();
								break;
							case SDL_TEXTINPUT:
								playerName += event.text.text;
								break;
							}
						}
						GraphicManager::clearScreen();
						GraphicManager::drawText(Config::getConfig().windowWidth / 2 - 430, 50, 86, 94, 255, 108, u8"ВВЕДИТЕ ИМЯ");
						GraphicManager::drawText(Config::getConfig().windowWidth / 2 - 128, Config::getConfig().windowHeight / 2, 255, 255, 255, 32, playerName);
						SDL_RenderPresent(objRenderer);
					}

					break;
				}
				case enums::GameEvent::LeaderBoard:
				{
					return new LeaderBoard(this, objRenderer);
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
	GraphicManager::drawText(titleOffsetX, 50, 86, 94, 255, 108,"XONIX");
}

bool MainMenu::init(SDL_Renderer* renderer)
{
	for (int i = 0; i < maxButtons; i++)
		if (!buttons[i]->init(renderer))
			return false;

	objRenderer = renderer;
	if (objRenderer == nullptr)
		return false;

	ResourceManager::getManager().init(renderer);
	GraphicManager::getManager().getRenderer() = renderer;
	BonusManager::getManager().init();

	if (!gameField->init(renderer))
		return false;
	return true;
}
