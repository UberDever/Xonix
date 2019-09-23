#pragma once

#include <iostream>
#include <chrono>
#include "Config.h"
#include "MainMenu.h"

class Game
{
private:

	bool isRunning;

private:

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

public:

	Game();

	bool onInit();
	int onExec();
	void onCleanUp();
};

