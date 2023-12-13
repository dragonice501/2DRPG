#pragma once

#include "../Components/Components.h"

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
	virtual void Render();

	virtual void UpdateAnimation();

	virtual const Vec2& GetPosition() const { return mPosition; }

public:
	Vec2 mPosition;
};