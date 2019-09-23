#pragma once

#include <SDL.h>
#include "../include/Enums.h"

class Scene
{
public:
	virtual Scene* handleEvent(const enums::GameEvent& event) = 0;
	virtual Scene* update(uint64_t delta) = 0;
	virtual void render() = 0;
	virtual bool init(SDL_Window* window) = 0;
	virtual ~Scene() {};
};