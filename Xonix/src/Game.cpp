#include "../include/Game.h"

Game::Game() : mainWindow(nullptr), mainRenderer(nullptr), isRunning(true)
{

}


bool Game::onInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	mainWindow = SDL_CreateWindow("Xonix!", 100, 100, globalConfig.windowWidth, globalConfig.windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

	globalConfig.load();

	if (!this->onInit())
		return 2;

	Scene* mainScene = new MainMenu();
	if (!mainScene->init(mainWindow))
		return 3;
	auto currentTime = std::chrono::system_clock::now();
	auto previousTime = std::chrono::system_clock::now();

	while (isRunning)
	{
		previousTime = currentTime;
		currentTime = std::chrono::system_clock::now();
		while (SDL_PollEvent(&rawEvent))
		{
			if (globalConfig.parseEvent(rawEvent, gameEvent))
				mainScene = mainScene->handleEvent(gameEvent);
			if (mainScene == nullptr)
				return 0;
		}

		mainScene = mainScene->update(std::chrono::duration_cast<std::chrono::microseconds>
			(currentTime - previousTime).count());
		if (mainScene == nullptr)
			return 0;

		mainScene->render();
	}

	this->onCleanUp();

	return 0;
}

void Game::onCleanUp()
{
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}
