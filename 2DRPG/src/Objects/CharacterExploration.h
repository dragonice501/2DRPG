#pragma once

#include "Actor.h"
#include "../Objects/ActorNpc.h"

#include "../Managers/InputManager.h"
#include "../Managers/PlayerManager.h"

class CharacterExploration : public Actor
{
public:
	CharacterExploration();
	~CharacterExploration();

	void Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation = "IdleDown") override;
	void LoadAnimations(std::string animationsFileName) override;
	void Input() override;
	void Update(const float dt) override;
	void Render(SDL_Renderer* renderer) override;
	void UpdateAnimation() override;
	const Vec2& GetPosition() const override { return mPosition; }

	void Setup(const int partyIndex, const Vec2& spawnPosition, const Vec2& spawnDirection);

	inline const ECharacterState GetCharacterState() const { return mCharacterState; }
	inline const SDL_Texture* GetSpriteSheet() const { return mSpriteSheet; }

	inline void SetCharacterState(const ECharacterState state) { mCharacterState = state; }
	inline void SetPosition(const Vec2& position) { mPosition = position; }
	inline void SetSpriteSheet(SDL_Texture* spriteSheet) { mSpriteSheet = spriteSheet; }

	void CheckInput(const int mapWidth, const int mapHeight, const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters);

	void UpdateMovement(
		const int mapWidth, const int mapHeight,
		const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters, const std::vector<ActorNpc>& actors,
		const float dt);
	bool MovementPressed();
	Vec2 GetDesiredPosition(const std::vector<CharacterExploration>& characters);
	bool MovementInsideMap(const Vec2& position, const int width, const int height);
	bool CanMove(
		const Vec2& desiredPosition, int width, int height,
		const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters, const std::vector<ActorNpc>& actors);
	void SetMovement(const std::vector<CharacterExploration>& characters);
	
	Movement mMovement;
	Rigidbody mRigidbody;
	int mPartyIndex;

private:
	EMovementState mMovementState = MS_IDLE;
	ECharacterState mCharacterState = CS_MOVING;
};