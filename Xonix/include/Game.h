#pragma once

#include <iostream>
#include <time.h>
#include "Config.h"
#include "MainMenu.h"

constexpr auto GAME_INIT = 1;
constexpr auto MENU_INIT = 2;

class Game
{
private:

	bool isRunning;

private:

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	uint32_t frameTime;

public:

	Game();

	bool onInit();
	int onExec();
	void onCleanUp();
};

