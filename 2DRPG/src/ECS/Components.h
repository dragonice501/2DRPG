#pragma once

#include "../Utils/Vec2.h"

#include <SDL.h>
#include <glm/vec2.hpp>

struct AnimationComponent
{
	AnimationComponent(int numFrames = 1, int frameRateSpeed = 1, bool shouldLoop = true)
	{
		this->numFrames = numFrames;
		this->currentFrame = 1;
		this->frameRateSpeed = frameRateSpeed;
		this->shouldLoop = shouldLoop;
		this->startTime = SDL_GetTicks();
	}

	int numFrames;
	int currentFrame;
	int frameRateSpeed;
	bool shouldLoop;
	int startTime;
};

struct BoxColliderComponent
{
	BoxColliderComponent(int width = 0, int height = 0, Vec2 offset = Vec2(0))
	{
		this->width = width;
		this->height = height;
		this->offset = offset;
	}

	int width;
	int height;
	Vec2 offset;
};

struct CameraFollowComponent
{
	CameraFollowComponent() = default;
};

struct HealthComponent
{
	HealthComponent(int healthPercentage = 0)
	{
		this->healthPercentage = healthPercentage;
	}

	int healthPercentage;
};

struct KeyboardControlComponent
{
	KeyboardControlComponent(
		Vec2 upVelocity = Vec2(0),
		Vec2 downVelocity = Vec2(0),
		Vec2 leftVelocity = Vec2(0),
		Vec2 rightVelocity = Vec2(0))
	{
		this->upVelocity = upVelocity;
		this->rightVelocity = rightVelocity;
		this->downVelocity = downVelocity;
		this->leftVelocity = leftVelocity;
	}

	Vec2 upVelocity;
	Vec2 rightVelocity;
	Vec2 downVelocity;
	Vec2 leftVelocity;
};

struct ProjectileComponent
{
	ProjectileComponent(bool isFriendly = false, int hitPercentDamage = 0, int duration = 0)
	{
		this->isFriendly = isFriendly;
		this->hitPercentDamage = hitPercentDamage;
		this->duration = duration;

		this->startTime = SDL_GetTicks();
	}

	bool isFriendly;
	int hitPercentDamage;
	int duration;
	int startTime;
};

struct ProjectileEmitterComponent
{
	ProjectileEmitterComponent(
		Vec2 projectileVelocity = Vec2(0),
		int repeatFrequency = 0,
		int projectileDuration = 10000,
		int hitPercentageDamage = 10,
		bool isFriendly = false)
	{
		this->projectileVelocity = projectileVelocity;
		this->repeatFrequency = repeatFrequency;
		this->projectileDuration = projectileDuration;
		this->hitPercentDamage = hitPercentageDamage;
		this->isFriendly = isFriendly;
	}

	Vec2 projectileVelocity;
	int repeatFrequency;
	int projectileDuration;
	int hitPercentDamage;
	bool isFriendly;
	int lastEmissionTime;
};

struct RigidbodyComponent
{
	RigidbodyComponent(Vec2 velocity = Vec2(0.0, 0.0))
	{
		this->velocity = velocity;
	}

	Vec2 velocity;
};

struct SpriteComponent
{
	SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int zIndex = 0, bool isFixed = false, int srcRectX = 0, int srcRectY = 0)
	{
		this->assetId = assetId;
		this->width = width;
		this->height = height;
		this->zIndex = zIndex;
		this->flip = SDL_FLIP_NONE;
		this->srcRect = { srcRectX, srcRectY, width, height };
		this->isFixed = isFixed;
	}

	std::string assetId;
	int width;
	int height;
	int zIndex;
	SDL_RendererFlip flip;
	bool isFixed;
	SDL_Rect srcRect;
};

struct TileComponent
{
	TileComponent()
	{

	}
};

struct TransformComponent
{
	TransformComponent(Vec2 position = Vec2(0, 0), Vec2 scale = Vec2(1, 1), double rotation = 0)
	{
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}

	Vec2 position;
	Vec2 scale;
	double rotation;
};

struct TextLabelComponent
{
	TextLabelComponent(
		Vec2 textPosition = Vec2(0),
		std::string text = "",
		std::string assetId = "",
		const SDL_Color& color = { 0, 0, 0 },
		bool isFixed = true)
	{
		this->position = textPosition;
		this->text = text;
		this->assetId = assetId;
		this->color = color;
		this->isFixed = isFixed;
	}

	Vec2 position;
	std::string text;
	std::string assetId;
	SDL_Color color;
	bool isFixed;
};