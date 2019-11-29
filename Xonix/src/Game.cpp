#include "../include/Game.h"

Game::Game() : mainWindow(nullptr), mainRenderer(nullptr), isRunning(true), frameTime(1000 / 60)
{

}


bool Game::onInit()
{

	Config::getConfig().load();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("IMG_Init: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}

	mainWindow = SDL_CreateWindow("Xonix!", 100, 100, Config::getConfig().windowWidth, Config::getConfig().windowHeight + 36 /*status bar offset*/, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mainWindow == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mainRenderer == nullptr) {
		std::cerr << "SDL_CreateRenderer Error" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	return true;
}

int Game::onExec()
{
	SDL_Event rawEvent;
	enums::GameEvent gameEvent;

	srand(time(nullptr));

	if (!this->onInit())
		return GAME_INIT;

	Scene* mainScene = new MainMenu();
	if (!mainScene->init(mainWindow))
		return MENU_INIT;

	uint32_t currentTime = SDL_GetTicks();

	while (isRunning)
	{
		if (currentTime + frameTime < SDL_GetTicks())
		{
			currentTime = SDL_GetTicks();

			while (SDL_PollEvent(&rawEvent))
			{
				if (Config::getConfig().parseEvent(rawEvent, gameEvent))
					mainScene = mainScene->handleEvent(gameEvent);
				if (mainScene == nullptr)
					return 0;
			}

			mainScene = mainScene->update();

			if (mainScene == nullptr)
			{
				isRunning = false;
				continue;
			}

			mainScene->render(mainRenderer);
			SDL_RenderPresent(mainRenderer);
		}
	}

	this->onCleanUp();

	return 0;
}

void Game::onCleanUp()
{
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	TTF_Quit(); 
	SDL_Quit();
}
