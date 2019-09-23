#pragma once

#include <SDL.h>
#include <unordered_map>
#include "../include/Enums.h"

class Config
{
public:

	std::unordered_map<SDL_Keycode, enums::GameEvent> eventMap;
	const int windowWidth = 1280;
	const int windowHeight = 1024;

public:

	Config()
	{
		eventMap[SDLK_w] = enums::GameEvent::Up;
		eventMap[SDLK_a] = enums::GameEvent::Left;
		eventMap[SDLK_s] = enums::GameEvent::Down;
		eventMap[SDLK_d] = enums::GameEvent::Right;
		eventMap[SDLK_ESCAPE] = enums::GameEvent::Quit;
		eventMap[SDLK_LEFT] = enums::GameEvent::ArrowLeft;
		eventMap[SDLK_RIGHT] = enums::GameEvent::ArrowRight;
		eventMap[SDLK_UP] = enums::GameEvent::ArrowUp;
		eventMap[SDLK_DOWN] = enums::GameEvent::ArrowDown;
	}

	void load()
	{

	}

	bool parseEvent(SDL_Event& rawEvent, enums::GameEvent& gameEvent)
	{
		if (rawEvent.type == SDL_KEYDOWN)
		{
			if (eventMap.find(rawEvent.key.keysym.sym) != eventMap.end())
			{
				gameEvent = eventMap[rawEvent.key.keysym.sym];
				return true;
			}
		}
		else if (rawEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			gameEvent = enums::GameEvent::MouseButtonPressed;
			return true;
		}
		return false;	
	}
};

static Config globalConfig;
