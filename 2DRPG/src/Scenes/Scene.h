#pragma once

#include "../Engine/Engine.h"

#include "../Utils/Constants.h"
#include "../Utils/Vec2.h"

#include <SDL.h>
#include <memory>
#include <fstream>
#include <string>

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Setup(SDL_Renderer* renderer) = 0;
	virtual void Shutdown() = 0;

	virtual void Input() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render(SDL_Renderer* renderer, SDL_Rect& camera) = 0;

protected:
	int mMapWidth = 0;
	int mMapHeight = 0;
	int mStartX = 0;
	int mStartY = 0;
};