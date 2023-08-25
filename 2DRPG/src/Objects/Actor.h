#pragma once

#include "Character.h"
#include "Components.h"
#include "../Utils/Vec2.h"
#include "../Utils/Constants.h"

#include "../Engine/Engine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <fstream>

class Actor
{
public:
	Actor();
	~Actor();

	void Init(const std::string& spriteSheetPath, const std::string& animationsFilePath, const Vec2& spawnPosition, SDL_Renderer* renderer);
	void LoadAnimations(std::string animationsFilePath);

	void Update(const float dt);
	void Render(SDL_Renderer* renderer);

	void UpdateAnimation();

	Vec2 position;

private:
	Sprite mSprite;
	SDL_Texture* mSpriteSheet;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;
};