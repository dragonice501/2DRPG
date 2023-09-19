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
	CharacterAttributes(
		std::string characterName = "", ECharacterClass characterClass = NO_CLASS,
		int level = 0, int health = 0, int healthMax = 0, int magic = 0, int magicMax = 0,
		int strength = 0, int defense = 0, int intelligence = 0, int speed = 0, int skill = 0, int luck = 0,
		int exp = 0, int expNextLevel = 0)
	{
		this->characterName = characterName;
		this->characterClass = characterClass;
		this->level = level;
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

		this->exp = exp;
		this->expNextLevel = expNextLevel;
	}

	std::string characterName;
	ECharacterClass characterClass;

	int level;
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

	int exp;
	int expNextLevel;
};

struct Movement
{
	Movement(Vec2 start = Vec2(0.0f), Vec2 destination = Vec2(0.0f), float rate = 0.0f)
	{
		this->start = start;
		this->destination = destination;
		this->rate = rate;
		stepTaken = false;
		this->upHeld = false;
		this->downHeld = false;
		this->rightHeld = false;
		this->leftHeld = false;
	}

	Vec2 start;
	Vec2 destination;
	float rate;
	bool stepTaken;

	bool upHeld;
	bool downHeld;
	bool rightHeld;
	bool leftHeld;
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
	SceneEntrance(const Vec2& position, const Vec2& spawnOffset, const std::string& sceneName, const int sceneEntranceIndex)
	{
		this->position = position;
		this->spawnOffset = spawnOffset;
		this->scene = GetSceneName(sceneName);
		this->sceneEntranceIndex = sceneEntranceIndex;
	}

	const SceneName GetSceneName(const std::string& sceneName)
	{
		if (sceneName == "Town")
		{
			return TOWN;
		}
		else if (sceneName == "Overworld")
		{
			return OVERWORLD;
		}
	}

	Vec2 position;
	Vec2 spawnOffset;
	SceneName scene;
	int sceneEntranceIndex;
};

struct Sprite
{
	Sprite(int srcX = 0, int srcY = 0, int width = 0, int height = 0, int xOffset = 0, int yOffset = 0)
	{
		this->srcRect = { srcX, srcY, width, height };
		this->positionOffset = Vec2(xOffset, yOffset);
	}

	SDL_Rect srcRect;
	Vec2 positionOffset;
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