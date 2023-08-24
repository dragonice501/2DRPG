#pragma once

#include "Character.h"
#include "../Utils/Vec2.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Character
{
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

		int numFrames;
		int currentFrame;
		int frameRateSpeed;
		bool shouldLoop;
		int startTime;
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

	struct Input
	{
		Input() : upPressed(false), downPressed(false), leftPressed(false), rightPressed(false)
		{

		}

		bool upPressed;
		bool downPressed;
		bool leftPressed;
		bool rightPressed;
	};

	struct Rigidbody
	{
		Rigidbody() : velocity(Vec2(0.0f))
		{

		}

		Vec2 velocity;
	};

public:
	Character();
	~Character();

	void Init(std::string mSpriteSheetPath, SDL_Renderer* renderer);

	void Update(const float dt);
	void Render(SDL_Renderer* renderer);

	Input mInput;
	Rigidbody mRigidbody;

private:

	Vec2 position;
	Sprite mSprite;
	SDL_Texture* mSpriteSheet;
	Animation mIdleAnimation;
};