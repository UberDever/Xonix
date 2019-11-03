#pragma once

#include "Scene.h"
#include "GameField.h"

class GamePlay: public Scene
{
private:

	Scene* gameField;

public:
	GamePlay(Scene*);
	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;
	bool init(SDL_Window* window) override;
};