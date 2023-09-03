#pragma once

#include "Actor.h"

#include "../Managers/InputManager.h"

class CharacterExploration : Actor
{
public:
	CharacterExploration();
	~CharacterExploration();

	void Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer,std::string startinAnimation = "IdleDown") override;
	void LoadAnimations(std::string animationsFileName) override;
	void Update(const float dt) override;
	void Render(SDL_Renderer* renderer) override;
	void UpdateAnimation() override;
	const Vec2& GetPosition() const override { return mPosition; }

	inline const ECharacterState GetCharacterState() const { return mCharacterState; }
	inline const SDL_Texture* GetSpriteSheet() const { return mSpriteSheet; }

	inline void SetCharacterState(const ECharacterState state) { mCharacterState = state; }
	inline void SetPosition(const Vec2& position) { mPosition = position; }
	inline void SetSpriteSheet(SDL_Texture* spriteSheet) { mSpriteSheet = spriteSheet; }

	void CheckInteracting();

	void UpdateMovement(const int mapWidth, const int mapHeight, const std::vector<Tile>& tiles, const std::vector<Actor>& actors, const float dt);
	bool MovementPressed();
	Vec2 GetDesiredPosition();
	bool MovementInsideMap(const Vec2& position, const int width, const int height);
	bool CanMove(const Vec2& desiredPosition, int width, int height, const std::vector<Tile>& tiles, const std::vector<Actor>& actors);
	void SetMovement();
	Movement mMovement;
	Rigidbody mRigidbody;

private:
	EMovementState mMovementState = MS_IDLE;
	ECharacterState mCharacterState = CS_MOVING;
};