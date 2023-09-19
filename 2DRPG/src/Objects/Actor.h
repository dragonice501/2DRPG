#pragma once

#include "Components.h"

#include "../Dialogue/Dialogue.h"
#include "../Utils/Vec2.h"
#include "../Utils/Constants.h"

#include "../Engine/Engine.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/InputManager.h"

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

	virtual void Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startingAnimation = "IdleDown");
	virtual void LoadAnimations(std::string animationsFilePath);

	virtual void Input();
	virtual void Update(const float dt);
	virtual void Render(SDL_Renderer* renderer);

	virtual void UpdateAnimation();

	inline void SetCurrentAnimation(const std::string& animation) { mCurrentAnimation = animation; }

	virtual const Vec2& GetPosition() const { return mPosition; }

public:
	Vec2 mPosition;
	Sprite mSprite;
	SDL_Texture* mSpriteSheet;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;
};