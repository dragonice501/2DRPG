#pragma once

#include "../Objects/Components.h"
#include "../Utils/Vec2.h"
#include "../Utils/Utils.h"

#include <SDL.h>

class ActorBattle
{
public:
	ActorBattle() {}
	virtual ~ActorBattle() {}

	const bool IsAlive() const { return attributes.health > 0; }

	Vec2 battlePosition;
	SDL_Rect rect;

	bool isEnemy = false;

	CharacterAttributes attributes;
	EElementAffect fireAffect;
};