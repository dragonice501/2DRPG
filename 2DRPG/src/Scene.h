#pragma once

#include "Engine.h"
#include "CharacterExploration.h"

#include "Constants.h"
#include "Vec2.h"

#include "AudioManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"

#include <SDL.h>
#include <memory>
#include <fstream>
#include <string>

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Setup(static SDL_Renderer* renderer) = 0;
	virtual void Shutdown() = 0;

	virtual void Input() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render(static SDL_Rect& camera) = 0;

	virtual void ExitMenu() = 0;

protected:
	int mMapWidth = 0;
	int mMapHeight = 0;
	int mStartX = 0;
	int mStartY = 0;
};