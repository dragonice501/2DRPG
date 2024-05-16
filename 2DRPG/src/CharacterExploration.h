#pragma once

#include "GameObject.h"

#include "Npc.h"

#include "Components.h"

#include "Tile.h"

#include "InputManager.h"
#include "GameManager.h"
#include "PlayerManager.h"

class CharacterExploration : public GameObject
{
public:
	CharacterExploration();
	~CharacterExploration();

	void Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation = "IdleDown");
	void LoadAnimations(std::string animationsFileName);
	
	void UpdateAnimation();

	void Input() override;
	void Update(const float dt) override;
	void Render() override;

	const Vec2& GetPosition() const { return mPosition; }

	void Setup(const int partyIndex, const Vec2& spawnPosition, const Vec2& spawnDirection, const std::string& startingAnimation = "IdleDown");

	inline const ECharacterState GetCharacterState() const { return mCharacterState; }
	inline const SDL_Texture* GetSpriteSheet() const { return mSpriteSheet; }

	inline void SetCharacterState(const ECharacterState state) { mCharacterState = state; }
	inline void SetPosition(const Vec2& position) { mPosition = position; }
	inline void SetSpriteSheet(SDL_Texture* spriteSheet) { mSpriteSheet = spriteSheet; }

	void CheckInput(const int mapWidth, const int mapHeight, const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters);

	void UpdateMovement(
		const int mapWidth, const int mapHeight,
		const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters, const std::vector<Npc>& actors,
		const float dt);
	bool MovementPressed();
	Vec2 GetDesiredPosition(const std::vector<CharacterExploration>& characters);
	bool MovementInsideMap(const Vec2& position, const int width, const int height);
	bool CanMove(
		const Vec2& desiredPosition, int width, int height,
		const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters, const std::vector<Npc>& actors);
	void SetMovement(const std::vector<CharacterExploration>& characters);
	void ResetMovement();
	
	Movement mMovement;
	Rigidbody mRigidbody;
	int mPartyIndex;
	EMovementState mMovementState = MS_IDLE;

	Vec2 mPosition;
	SpriteComponent mSprite;

	SDL_Texture* mSpriteSheet;
	std::string mAssetID;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;

private:
	ECharacterState mCharacterState = CS_MOVING;
};