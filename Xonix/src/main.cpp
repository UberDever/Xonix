﻿#include <iostream>
#include "../include/Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();
	return game->onExec();
}
