#pragma once

#include "../Engine/Engine.h"

#include "../Utils/Constants.h"
#include "../Utils/Vec2.h"

#include <SDL.h>
#include <memory>
#include <fstream>

class SceneRef
{
public:
	virtual ~SceneRef() {};

	virtual void Setup(SDL_Renderer* renderer) = 0;
	virtual void Shutdown() = 0;

	virtual void Input() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

protected:
	int mapWidth = 0;
	int mapHeight = 0;
	int startX = 0;
	int startY = 0;

	std::string sceneFileString = "";
	Vec2 spawnPosition = Vec2(0.0f);
};