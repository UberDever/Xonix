#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Config.h"
#include "Scene.h"
#include "GameField.h"

class Button
{
private:
	int x, y, w, h;
	SDL_Texture* buttonTexture;
	SDL_Renderer* objRenderer;
	SDL_Rect rect;
	enums::GameEvent event;
	std::string name;

public:
	Button(int X, int Y, int W, int H): x(X), y(Y),
		w(W), h(H), buttonTexture(nullptr), objRenderer(nullptr), event(enums::GameEvent::Quit) {
		rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	}

	~Button() { SDL_DestroyTexture(buttonTexture); }

	bool init(SDL_Window* window)
	{
		SDL_Surface* tempSurf = nullptr;
		SDL_Color color = { 255, 255, 255 };
		tempSurf = IMG_Load("data/sprites/button.png");
		tempSurf = SDL_ConvertSurfaceFormat(tempSurf, SDL_PIXELFORMAT_ARGB8888, 0);
		if (tempSurf == nullptr)
			return false;
		TTF_Font* font = nullptr;
		font = TTF_OpenFont("data/fonts/font.ttf", 32);
		if (font == nullptr)
			return false;
		SDL_Surface* tempText = nullptr;
		tempText = TTF_RenderUTF8_Blended(font, name.c_str(), color);
		if (tempText != nullptr)
		{
			SDL_Rect dstRect = { (this->w / 2 - tempText->w / 2), (this->h / 2 - tempText->h / 2), 0, 0 };
			SDL_BlitSurface(tempText, nullptr, tempSurf, &dstRect);
		}
		TTF_CloseFont(font);
		buttonTexture = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), tempSurf);
		SDL_FreeSurface(tempText);
		SDL_FreeSurface(tempSurf);
		if (buttonTexture == nullptr)
			return false;
		objRenderer = SDL_GetRenderer(window);
		if (objRenderer == nullptr)
			return false;
		return true;
	}

	void render() { SDL_RenderCopy(objRenderer, buttonTexture, nullptr, &rect); }

	int getX() { return x; }
	int getY() { return y; }

	enums::GameEvent& getEvent() { return event; }
	std::string& getString() { return name; }
};

class ScreenSaver
{

};

class MainMenu : public Scene
{
private:
	static constexpr int maxButtons = 4;
	static constexpr int buttonHeight = 100;
	static constexpr int buttonWidth = 400;
	static constexpr int offset = 20;
	int buttonStartX, buttonStartY, buttonEndX, buttonEndY;
	SDL_Renderer* objRenderer;
	Button *buttons[maxButtons];

	GameField* gameField;

public:
	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update() override;
	void render(SDL_Renderer* renderer) override;

	bool init(SDL_Window* window) override;

	MainMenu();
	~MainMenu();
};
