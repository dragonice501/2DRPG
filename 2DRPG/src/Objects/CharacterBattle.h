#pragma once

#include "Actor.h"
#include "../Objects/Components.h"

#include <SDL.h>
#include <string>

class CharacterBattle
{
public:
	CharacterBattle();

	void LoadAnimations(std::string name);

	void Render(SDL_Renderer* renderer);

	size_t battleSpawnPosition;
	SDL_Rect rect;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation = "IdleLeft";
	Sprite mSprite;
};