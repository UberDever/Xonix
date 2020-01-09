#pragma once

#include <fstream>

#include "Scene.h"
#include "MainMenu.h"
#include "GraphicManager.h"

class Button;

class LeaderBoard : public Scene
{
private:

	static constexpr int buttonHeight = 100;
	static constexpr int buttonWidth = 400;
	static constexpr int lbCount = 15;
	int buttonStartX, buttonStartY, buttonEndX, buttonEndY;

	Scene* mainMenu;
	SDL_Renderer* objRenderer;
	std::fstream lbFile;
	std::pair<std::string, int> lb[15];
	Button* btn;

public:

	LeaderBoard(Scene*, SDL_Renderer*);
	LeaderBoard(int _score, std::string _name, SDL_Renderer* _objRenderer);
	~LeaderBoard();

	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;
	bool init(SDL_Renderer* renderer) override;
};