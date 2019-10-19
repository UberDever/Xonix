#pragma once

#include <SDL.h>
#include <unordered_map>
#include "../include/Enums.h"

class Config
{
private:

	Config()
	{
		eventMap[SDLK_w] = enums::GameEvent::Up;
		eventMap[SDLK_a] = enums::GameEvent::Left;
		eventMap[SDLK_s] = enums::GameEvent::Down;
		eventMap[SDLK_d] = enums::GameEvent::Right;
		eventMap[SDLK_ESCAPE] = enums::GameEvent::Quit;
	}

	Config(const Config&) = delete;
	Config& operator=(Config&) = delete;

public:

	std::unordered_map<SDL_Keycode, enums::GameEvent> eventMap;
	const int windowWidth = 1440;
	const int windowHeight = 900;

public:

	void load()
	{

	}

	static Config& getConfig()
	{
		static Config instance;
		return instance;
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
