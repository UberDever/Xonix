#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <unordered_map>

class GraphicManager
{
private:

	static SDL_Renderer* renderer;
	static std::unordered_map<int, TTF_Font*>* fonts;

	GraphicManager(const GraphicManager&) = delete;
	GraphicManager& operator=(GraphicManager&) = delete;

	GraphicManager() { fonts = new std::unordered_map<int, TTF_Font*>; fonts->reserve(5); };
	~GraphicManager() { fonts->clear(); };
public:

	static GraphicManager& getManager()
	{
		static GraphicManager instance;
		return instance;
	}

	static SDL_Renderer*& getRenderer()	{ return renderer; }

	static void drawText(int X, int Y, uint8_t R, uint8_t G, uint8_t B, int size, std::string text);
	static void drawText(int X, int Y, uint8_t R, uint8_t G, uint8_t B, int size, int num);
};