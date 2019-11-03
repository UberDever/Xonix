#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Config.h"
#include "ResourceManager.h"
#include "GraphicManager.h"
#include "Scene.h"
#include "GamePlay.h"
#include "GameField.h"

class Button
{
private:
	int x, y, w, h;
	bool Visible;
	SDL_Texture* buttonTexture;
	SDL_Renderer* objRenderer;
	SDL_Rect rect;
	enums::GameEvent event;
	std::string name;

public:
	Button(int X, int Y, int W, int H) : x(X), y(Y),
		w(W), h(H), buttonTexture(nullptr), objRenderer(nullptr), event(enums::GameEvent::Quit), Visible(false) {
		rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	}

	~Button() { SDL_DestroyTexture(buttonTexture); }

	bool init(SDL_Window* window);

	void render() { SDL_RenderCopy(objRenderer, buttonTexture, nullptr, &rect); }

	int getX() { return x; }
	int getY() { return y; }

	enums::GameEvent& getEvent() { return event; }
	std::string& getString() { return name; }
	bool& isVisible() { return Visible; }
};

class MainMenu : public Scene
{
private:
	static constexpr int maxButtons = 14;
	static constexpr int mainScreenButtons = 4;
	static constexpr int buttonHeight = 100;
	static constexpr int buttonWidth = 400;
	static constexpr int offsetY = 20;
	static constexpr int offsetX = 100;
	static constexpr int buttonsInColumn = (maxButtons - mainScreenButtons) / 2;
	int buttonStartX, buttonStartY, buttonEndX, buttonEndY;
	SDL_Renderer* objRenderer;
	Button *buttons[maxButtons];

	Scene* gameField;

public:
	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;

	bool init(SDL_Window* window);

	MainMenu();
	~MainMenu();
};
