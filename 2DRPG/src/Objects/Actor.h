#pragma once

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

	virtual void Init(const std::string& spriteSheetPath, const std::string& animationsFilePath, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation = "IdleDown");
	virtual void LoadAnimations(std::string animationsFilePath);

	virtual void Update(const float dt);
	virtual void Render(SDL_Renderer* renderer);

	virtual void UpdateAnimation();

	virtual const Vec2& GetPosition() const { return mPosition; }


protected:
	Vec2 mPosition;
	Sprite mSprite;
	SDL_Texture* mSpriteSheet;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;
};