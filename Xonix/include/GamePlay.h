#pragma once

#include "Scene.h"
#include "MainMenu.h"
#include "GameField.h"

class GamePlay: public Scene
{
private:

	Scene* gameField;
	SDL_Renderer* objRenderer;
	std::string name;
	int score;

public:
	GamePlay(std::string, Scene*, SDL_Renderer*);
	~GamePlay();
	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;
	bool init(SDL_Renderer* renderer) override { return true; };
};

class Button;

class Pause: public Scene
{
private:

	Scene* pausedGame;
	SDL_Renderer* objRenderer;

	Button* buttons[2];
	static constexpr int buttonHeight = 100;
	static constexpr int buttonWidth = 400;
	static constexpr int offsetY = 20;
	static constexpr int offsetX = 100;
	int buttonStartX, buttonStartY, buttonEndX, buttonEndY;

public:

	Pause(Scene* gamePlay, SDL_Renderer*);
	~Pause();

	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;
	bool init(SDL_Renderer* renderer) override;
};