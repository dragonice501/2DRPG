#pragma once

#include "../Utils/Utils.h"
#include "../Utils/Vec2.h"

#include <SDL.h>
#include <vector>
#include <map>
#include <string>
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

struct CharacterAttributes
{
	CharacterAttributes(std::string characterName = "", int health = 0, int healthMax = 0, int magic = 0, int magicMax = 0, int strength = 0, int defense = 0, int intelligence = 0, int speed = 0, int skill = 0, int luck = 0)
	{
		this->characterName = characterName;
		this->health = health;
		this->healthMax = healthMax;
		this->magic = magic;
		this->magicMax = magicMax;
		this->strength = strength;
		this->defense = defense;
		this->intelligence = intelligence;
		this->speed = speed;
		this->skill = skill;
		this->luck = luck;
	}

	std::string characterName;

	int health;
	int healthMax;
	int magic;
	int magicMax;
	int strength;
	int defense;
	int intelligence;
	int speed;
	int skill;
	int luck;
};

struct Movement
{
	Movement(Vec2 start = Vec2(0.0f), Vec2 destination = Vec2(0.0f), float rate = 0.0f)
	{
		this->start = start;
		this->destination = destination;
		this->rate = rate;
		stepTaken = false;
	}

	Vec2 start;
	Vec2 destination;
	float rate;
	bool stepTaken;
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

struct SceneEntrance
{
	SceneEntrance(const Vec2& position, const Vec2& spawnOffset, const int sceneName, const int sceneEntranceIndex)
	{
		this->position = position;
		this->spawnOffset = spawnOffset;
		this->sceneName = sceneName;
		this->sceneEntranceIndex = sceneEntranceIndex;
	}

	Vec2 position;
	Vec2 spawnOffset;
	int sceneName;
	int sceneEntranceIndex;
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