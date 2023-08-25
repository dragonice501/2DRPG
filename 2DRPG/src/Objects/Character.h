#pragma once

#include "Character.h"
#include "Components.h"
#include "../Utils/Vec2.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <map>

class Character
{
	enum EMovementState
	{
		MS_IDLE,
		MS_MOVING
	};

public:
	Character();
	~Character();

	void Init(const std::string& spriteSheetName, const std::string& animationsFileName, const Vec2& spawnPosition, SDL_Renderer* renderer);
	void LoadAnimations(std::string animationsFileName);

	void Update(const float dt);
	void Render(SDL_Renderer* renderer);

	void UpdateMovement(const int mapWidth, const int mapHeight, const std::vector<Tile>& mTiles, const float dt);
	bool MovementPressed();
	Vec2 GetDesiredPosition();
	bool MovementInsideMap(const Vec2& position, const int width, const int height);
	bool CanMove(const Vec2& desiredPosition, int width, int height, const std::vector<Tile>& mTiles);
	void SetMovement();

	void UpdateAnimation();

	Vec2 position;
	Input mInput;
	Movement mMovement;
	Rigidbody mRigidbody;

private:
	EMovementState mMovementState = MS_IDLE;
	Sprite mSprite;
	SDL_Texture* mSpriteSheet;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;
};