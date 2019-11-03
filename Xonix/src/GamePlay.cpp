#include "../include/GamePlay.h"

GamePlay::GamePlay(Scene* _gameField)
{
	gameField = _gameField;
}

Scene* GamePlay::handleEvent(const enums::GameEvent& event)
{
	switch (event)
	{
	case enums::GameEvent::Quit:
	{
		delete this;
		return nullptr;
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
	gameField = gameField->update();
	if (gameField == nullptr)
	{
		delete this;
		return nullptr;
	}
	return this;
}

void GamePlay::render(SDL_Renderer* renderer)
{
	gameField->render(renderer);
}

bool GamePlay::init(SDL_Window* window)
{
	gameField->init(window);
	return true;
}
