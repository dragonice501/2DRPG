#pragma once

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"
#include "../Utils/Utils.h"

#include <SDL.h>
#include <iostream>

class CharacterMovementEvent : public Event
{
public:
	CharacterMovementEvent(ETerrainType terrain, Vec2 movementPosition)
	{
		this->terrainType = terrain;
		this->position = movementPosition;
	}

	ETerrainType terrainType;
	Vec2 position;
};

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

class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(SDL_Keycode symbol)
	{
		this->symbol = symbol;
	}

	SDL_Keycode symbol;
};