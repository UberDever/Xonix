#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

class GraphicManager
{
private:

	static SDL_Renderer* renderer;
	static TTF_Font* font;

	GraphicManager(const GraphicManager&) = delete;
	GraphicManager& operator=(GraphicManager&) = delete;

	GraphicManager() {};
	~GraphicManager() {};
public:

	static GraphicManager& getManager()
	{
		static GraphicManager instance;
		return instance;
	}

	static SDL_Renderer*& getRenderer()	{ return renderer; }
	static TTF_Font*& getFont()			{ return font; }

	static void drawText(int X, int Y, int R, int G, int B, std::string text);
};