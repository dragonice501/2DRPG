#pragma once

#include "ActorBattle.h"
#include "../Objects/Components.h"

#include <SDL.h>
#include <string>
#include <fstream>

class CharacterBattle : public ActorBattle
{
public:
	CharacterBattle() {}
	~CharacterBattle() {}

	void LoadAnimations(std::string name);

	void Render();

	size_t battleSpawnPosition;
	SDL_Rect rect;

	std::string mAssetID;
	SDL_Texture* mTexture;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation = "IdleLeft";
	Sprite mSprite;
};