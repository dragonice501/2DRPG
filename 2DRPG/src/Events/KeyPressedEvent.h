#pragma once

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

#include <SDL.h>

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(SDL_Keycode symbol)
	{
		this->symbol = symbol;
	}

	SDL_Keycode symbol;
};