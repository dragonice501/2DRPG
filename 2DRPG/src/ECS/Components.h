#pragma once

#include "../Utils/Vec2.h"
#include "../Utils/Utils.h"

#include <SDL.h>
#include <glm/vec2.hpp>
#include <iostream>
#include <map>

struct AnimationComponent
{
	AnimationComponent(int numFrames = 1, int frameRateSpeed = 1, bool shouldLoop = true, std::string assetId = "")
	{
		this->assetId = assetId;
		this->numFrames = numFrames;
		this->currentFrame = 1;
		this->frameRateSpeed = frameRateSpeed;
		this->shouldLoop = shouldLoop;
		this->startTime = SDL_GetTicks();
	}

	std::string assetId;
	int numFrames;
	int currentFrame;
	int frameRateSpeed;
	bool shouldLoop;
	int startTime;
};

struct AnimationStateComponent
{
	enum AnimationState
	{
		IDLE,
		MOVING
	};

	AnimationStateComponent()
	{
		this->animationState = IDLE;
	}

	AnimationState animationState;
};

struct AnimationSystemComponent
{
	struct Animation
	{
		Animation(int numFrames = 1, int frameRateSpeed = 1, bool shouldLoop = true, std::string assetId = "")
		{
			this->assetId = assetId;
			this->numFrames = numFrames;
			this->currentFrame = 1;
			this->frameRateSpeed = frameRateSpeed;
			this->shouldLoop = shouldLoop;
			this->startTime = SDL_GetTicks();
		}

		std::string assetId;
		int numFrames;
		int currentFrame;
		int frameRateSpeed;
		bool shouldLoop;
		int startTime;
	};

	AnimationSystemComponent()
	{
		currentAnimation = "Idle";
	}

	void AddAnimation(std::string name, Animation animation)
	{
		animationMap.emplace(name, animation);
	}

	Animation& GetAnimation(const std::string& key) { return animationMap.at(key); }
	Animation& GetCurrentAnimation() { return animationMap.at(currentAnimation); }
	void SetCurrentAnimation(const std::string& key) { currentAnimation = key; }

	std::map<std::string, Animation> animationMap;
	std::string currentAnimation;
};

struct BoxColliderAAComponent
{
	BoxColliderAAComponent(int width = 16, int height = 16, Vec2 position = Vec2(0.0f))
	{
		this->width = width;
		this->height = height;
		this->position = position;
	}

	Vec2 position;
	int width;
	int height;
};

struct CameraFollowComponent
{
	CameraFollowComponent() : inHorizontalMiddle(false), inVerticalMiddle(false)
	{

	}

	bool inHorizontalMiddle;
	bool inVerticalMiddle;
};

struct CharacterInputComponent
{
	CharacterInputComponent() :
		upButtonPresed(false),
		downButtonPresed(false),
		leftButtonPresed(false),
		rightButtonPresed(false),
		interactButtonPressed(false), interactButtonHeld(false), interactButtonReleased(false)
	{

	}

	bool upButtonPresed;
	bool downButtonPresed;
	bool leftButtonPresed;
	bool rightButtonPresed;

	bool interactButtonPressed;
	bool interactButtonHeld;
	bool interactButtonReleased;
};

struct CharacterMovementComponent
{
	CharacterMovementComponent() :
		movementState(EMovementState::Idle), start(Vec2(0.0f)), destination(Vec2(0.0f)), rate(0.0f),
		upVelocity(0.0f, -1.0f), downVelocity(0.0f, 1.0f), leftVelocity(-1.0f, 0.0f), rightVelocity(1.0f, 0.0f)
	{
		canWalkCliffs = false;
		canWalkRivers = false;
		canWalkMountains = false;
	}

	enum EMovementState
	{
		Idle, Moving
	};

	EMovementState movementState;
	Vec2 start;
	Vec2 destination;
	float rate;

	Vec2 upVelocity;
	Vec2 rightVelocity;
	Vec2 downVelocity;
	Vec2 leftVelocity;

	bool canWalkCliffs;
	bool canWalkRivers;
	bool canWalkMountains;
};

struct HealthComponent
{
	HealthComponent(int healthPercentage = 0)
	{
		this->healthPercentage = healthPercentage;
	}

	int healthPercentage;
};

struct InteractableComponent
{
	InteractableComponent()
	{

	}
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
	RigidbodyComponent(Vec2 velocity = Vec2(0.0, 0.0), Vec2 lastVelocity = Vec2(-1.0f, 0.0f))
	{
		this->velocity = velocity;
		this->lastVelocity = lastVelocity;
	}

	Vec2 velocity;
	Vec2 lastVelocity;
};

struct SceneEntranceComponent
{
public:
	SceneEntranceComponent(int name = 0, int index = 0, Vec2 newPosition = Vec2(0.0f))
	{
		this->sceneName = name;
		this->sceneEntranceIndex = index;
		this->position = newPosition;

		//std::cout << "entrance created" << std::endl;
	}

	int sceneName;
	int sceneEntranceIndex;
	Vec2 position;
};

struct SpriteComponent
{
	SpriteComponent(
		std::string assetId = "",
		int width = 0, int height = 0, int xOffset = 0, int yOffset = 0,
		int zIndex = 0, bool isFixed = false, int srcRectX = 0, int srcRectY = 0)
	{
		this->assetId = assetId;
		this->width = width;
		this->height = height;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->zIndex = zIndex;
		this->flip = SDL_FLIP_NONE;
		this->srcRect = { srcRectX, srcRectY, width, height };
		this->isFixed = isFixed;
	}

	std::string assetId;
	int width;
	int height;
	int xOffset;
	int yOffset;
	int zIndex;
	SDL_RendererFlip flip;
	bool isFixed;
	SDL_Rect srcRect;
};

struct TileComponent
{
	TileComponent(int tileIndex = 0, bool isTownTile = false) : townTileType(UNWALKABLE), terrainType(UNDEFINED)
	{
		if (isTownTile)
		{
			this->townTileType = GetTownTileType(tileIndex);
		}
		else
		{
			this->terrainType = GetTerrainType(tileIndex);
		}
	}

	ETownTileType townTileType;
	ETerrainType terrainType;
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