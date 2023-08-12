#pragma once

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

#include <SDL.h>

class CollisionEvent : public Event
{
public:
	CollisionEvent(Entity a, Entity b) : a(a), b(b) {}

	Entity a;
	Entity b;
};

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(SDL_Keycode symbol)
	{
		this->symbol = symbol;
	}

	SDL_Keycode symbol;
};