#include "../include/GraphicManager.h"

SDL_Renderer* GraphicManager::renderer = nullptr;
TTF_Font* GraphicManager::font = nullptr;

void GraphicManager::drawText(int X, int Y, int R, int G, int B, std::string text)
{
	if (renderer == nullptr || font == nullptr)
		return;
	SDL_Color c = { R, G, B };
	SDL_Rect r = { X, Y };
	SDL_Surface* tempS = TTF_RenderText_Blended(font, text.c_str(), c);
	SDL_Texture* tempT = SDL_CreateTextureFromSurface(renderer, tempS);
	SDL_QueryTexture(tempT, nullptr, nullptr, &r.w, &r.h);
	SDL_RenderCopy(renderer, tempT, nullptr, &r);
	SDL_FreeSurface(tempS);
	SDL_DestroyTexture(tempT);
}
