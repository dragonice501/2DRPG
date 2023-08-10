#pragma once

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
	BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0))
	{
		this->width = width;
		this->height = height;
		this->offset = offset;
	}

	int width;
	int height;
	glm::vec2 offset;
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
		glm::vec2 upVelocity = glm::vec2(0),
		glm::vec2 rightVelocity = glm::vec2(0),
		glm::vec2 downVelocity = glm::vec2(0),
		glm::vec2 leftVelocity = glm::vec2(0))
	{
		this->upVelocity = upVelocity;
		this->rightVelocity = rightVelocity;
		this->downVelocity = downVelocity;
		this->leftVelocity = leftVelocity;
	}

	glm::vec2 upVelocity;
	glm::vec2 rightVelocity;
	glm::vec2 downVelocity;
	glm::vec2 leftVelocity;
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
		glm::vec2 projectileVelocity = glm::vec2(0),
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

	glm::vec2 projectileVelocity;
	int repeatFrequency;
	int projectileDuration;
	int hitPercentDamage;
	bool isFriendly;
	int lastEmissionTime;
};

struct RigidbodyComponent
{
	RigidbodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0))
	{
		this->velocity = velocity;
	}

	glm::vec2 velocity;
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

struct TransformComponent
{
	TransformComponent(glm::vec2 position = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), double rotation = 0)
	{
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}

	glm::vec2 position;
	glm::vec2 scale;
	double rotation;
};

struct TextLabelComponent
{
	TextLabelComponent(
		glm::vec2 textPosition = glm::vec2(0),
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

	glm::vec2 position;
	std::string text;
	std::string assetId;
	SDL_Color color;
	bool isFixed;
};