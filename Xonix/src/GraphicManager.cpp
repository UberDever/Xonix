#include "../include/GraphicManager.h"

SDL_Renderer* GraphicManager::renderer = nullptr;
std::unordered_map<int, TTF_Font*>* GraphicManager::fonts = nullptr;

void GraphicManager::drawText(int X, int Y, uint8_t R, uint8_t G, uint8_t B, int size, std::string text)
{
	if (renderer == nullptr)
		return;
	SDL_Color c = { R, G, B, 0xff };
	SDL_Rect r = { X, Y };
	if (fonts->find(size) == fonts->end())
	{
		(*fonts)[size] = TTF_OpenFont("data/fonts/font.ttf", size);
	}
	SDL_Surface* tempS = TTF_RenderText_Blended((*fonts)[size], text.c_str(), c);
	SDL_Texture* tempT = SDL_CreateTextureFromSurface(renderer, tempS);
	SDL_QueryTexture(tempT, nullptr, nullptr, &r.w, &r.h);
	SDL_RenderCopy(renderer, tempT, nullptr, &r);
	SDL_FreeSurface(tempS);
	SDL_DestroyTexture(tempT);
}

void GraphicManager::drawText(int X, int Y, uint8_t R, uint8_t G, uint8_t B, int size, int num)
{
	if (renderer == nullptr)
		return;
	SDL_Color c = { R, G, B, 0xff };
	SDL_Rect r = { X, Y };
	if (fonts->find(size) == fonts->end())
	{
		(*fonts)[size] = TTF_OpenFont("data/fonts/font.ttf", size);
	}
	SDL_Surface* tempS = TTF_RenderText_Blended((*fonts)[size], std::to_string(num).c_str(), c);
	SDL_Texture* tempT = SDL_CreateTextureFromSurface(renderer, tempS);
	SDL_QueryTexture(tempT, nullptr, nullptr, &r.w, &r.h);
	SDL_RenderCopy(renderer, tempT, nullptr, &r);
	SDL_FreeSurface(tempS);
	SDL_DestroyTexture(tempT);
}
