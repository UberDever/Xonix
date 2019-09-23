#include <SDL.h>
#include "./Config.h"
#include "./Scene.h"
#include <iostream>

class Button
{
private:
	int x, y, w, h;
	SDL_Texture* buttonTexture;
	SDL_Renderer* objRenderer;
	SDL_Rect rect;

public:
	Button(int X, int Y, int W, int H): x(X), y(Y),
		w(W), h(H), buttonTexture(nullptr), objRenderer(nullptr) {
		rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	}
	~Button() { SDL_DestroyTexture(buttonTexture); }
	bool init(SDL_Window* window)
	{
		SDL_Surface* tempSurf;
		tempSurf = SDL_LoadBMP("data/sprites/button.bmp");
		if (tempSurf == nullptr)
			return false;
		buttonTexture = SDL_CreateTextureFromSurface(SDL_GetRenderer(window) , tempSurf);
		SDL_FreeSurface(tempSurf);
		if (buttonTexture == nullptr)
			return false;
		objRenderer = SDL_GetRenderer(window);
		if (objRenderer == nullptr)
			return false;
		return true;
	}
	void render()
	{
		SDL_RenderCopy(objRenderer, buttonTexture, nullptr, &rect);
	}
};

class MainMenu : public Scene
{
private:
	static constexpr int MAX_BUTTONS = 4;
	SDL_Renderer* objRenderer;
	Button *buttons[MAX_BUTTONS];

public:
	Scene* handleEvent(const enums::GameEvent& event) override;
	Scene* update(uint64_t delta) override;
	void render() override;

	bool init(SDL_Window* window) override;

	MainMenu();
	~MainMenu();
};
