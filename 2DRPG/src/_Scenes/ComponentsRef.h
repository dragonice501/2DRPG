#pragma once

#include "../Utils/Utils.h"
#include "../Utils/Vec2.h"

#include <SDL.h>
#include <vector>
#include <map>
#include <iostream>

struct AnimationFrame
{
	AnimationFrame(Vec2 position = Vec2(0.0f), const int width = 0, const int height = 0)
	{
		this->position = position;
		this->width = width;
		this->height = height;
	}

	Vec2 position;
	int width;
	int height;
};

struct Animation
{
	Animation(int numFrames = 1, int frameRateSpeed = 1, bool shouldLoop = true)
	{
		this->numFrames = numFrames;
		this->currentFrame = 1;
		this->frameRateSpeed = frameRateSpeed;
		this->shouldLoop = shouldLoop;
		this->startTime = SDL_GetTicks();
	}
	
	std::vector<AnimationFrame> frames;
	int numFrames;
	int currentFrame;
	int frameRateSpeed;
	bool shouldLoop;
	int startTime;
};

struct Input
{
	Input(bool upPressed = false, bool downPressed = false, bool leftPressed = false, bool rightPressed = false)
	{
		this->upPressed = upPressed;
		this->downPressed = downPressed;
		this->leftPressed = leftPressed;
		this->rightPressed = rightPressed;
	}

	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
};

struct Movement
{
	Movement(Vec2 start = Vec2(0.0f), Vec2 destination = Vec2(0.0f), float rate = 0.0f)
	{
		this->start = start;
		this->destination = destination;
		this->rate = rate;
	}

	Vec2 start;
	Vec2 destination;
	float rate;
};

struct Rigidbody
{
	Rigidbody()
	{
		this->velocity = Vec2(0.0f);
		this->lastVelocity = Vec2(0.0f);
	}

	Vec2 velocity;
	Vec2 lastVelocity;
};

struct Sprite
{
	Sprite(int width = 0, int height = 0, int xOffset = 0, int yOffset = 0, int srcRectX = 0, int srcRectY = 0)
	{
		this->width = width;
		this->height = height;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->srcRect = { srcRectX, srcRectY, width, height };
	}

	int width;
	int height;
	int xOffset;
	int yOffset;
	SDL_Rect srcRect;
};

struct Tile
{
	Tile(const size_t spriteIndex, const Vec2 position)
	{
		this->spriteIndex = spriteIndex;
		this->position = position;

		terrainType = GetTerrainType(spriteIndex);
		townType = GetTownTileType(spriteIndex);
	}

	size_t spriteIndex;
	Vec2 position;
	ETerrainType terrainType;
	ETownTileType townType;
};