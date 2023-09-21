#pragma once

#include "Scene.h"
#include "../Utils/Utils.h"
#include "../Objects/Enemy.h"
#include "../Objects/EnemyEncounter.h"
#include "../Objects/ActorBattle.h"
#include "../Objects/CharacterBattle.h"
#include "../Objects/EnemyBattle.h"

#include "../Graphics/Font.h"

#include "../Managers/SceneManager.h"
#include "../Managers/PlayerManager.h"

#include <SDL.h>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <time.h>

class SceneBattle : public Scene
{
public:
	SceneBattle() : SceneBattle(PLAIN, std::vector<EnemyEncounter>()) {}
	SceneBattle(ETerrainType terrain, const std::vector<EnemyEncounter> enemyEncounters);

	void Setup(static SDL_Renderer* renderer);
	void Shutdown();

	void Input();
	void Update(const float dt);

	void ExitMenu() override {}

	void BuildTurnOrder();
	void NextTurn();

	void Render(static SDL_Renderer* renderer, static SDL_Rect& camera);
	void DrawActions(static SDL_Renderer* renderer, SDL_Rect& rect);
	void DrawPartyStats(static SDL_Renderer* renderer, SDL_Rect& rect);
	void DrawCursor(static SDL_Renderer* renderer);
	void DrawBattleEvent(static SDL_Renderer* renderer, SDL_Rect& rect, const std::string& eventString);

private:
	SDL_Texture* mBackgroundTexture = nullptr;
	std::string mBackgroundImageFilePath;

	SDL_Texture* mBattleIconsTexture = nullptr;
	std::string mBattleIconsFilePath = "./assets/MenuIcons.png";
	std::map<std::string, Sprite> mBattleIconsMap;

	SDL_Texture* mEnemiesTexture = nullptr;
	std::map<std::string, Enemy> mEnemyMap;
	std::vector<Enemy> mEnemies;
	
	EBattleState mBattleState = BS_SELECTING_ACTION;

	std::vector<CharacterBattle> mPlayerCharacters;
	std::vector<EnemyEncounter> mEnemyEncounters;

	std::vector<ActorBattle*> mBattleTurns;
	std::vector<CharacterBattle*> mBattleCharacters;
	std::vector<EnemyBattle*> mBattleEnemies;

	struct Turn
	{
		std::string characterName;
		bool partyMember;
		int characterIndex;
		int characterSpeed;
	};

	std::vector<Turn> mTurnOrder;
	int mTurnIndex = 0;

	int mBattleMenuIndex = 0;
	int mBattleMenuIndexOptions = 4;

	int mSelectedCharacterIndex = 0;
	int mBattleSelectedEnemyIndex = 0;

	float mTurnTime = 1.5f;
	float mTurnTimeRemaining = mTurnTime;
	float mBattleEndTime = 2.0f;
	float mBattleEndTimeRemaing = mBattleEndTime;

	int mDamageDealt = 0;
	int mEnemyTargetIndex = 0;
	int mCurrentPlayerIndex = 0;

	std::vector<Vec2> mPlayerCharacterPositions =
	{
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE),
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE) + Vec2(16.0f, 16.0f) * TILE_SPRITE_SCALE,
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE) + Vec2(32.0f, 32.0f) * TILE_SPRITE_SCALE,
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE) + Vec2(48.0f, 48.0f) * TILE_SPRITE_SCALE
	};

	std::vector<Vec2> mSmallEnemyPositions =
	{
		Vec2(0.0f, 0.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(0.0f, 1.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(0.0f, 2.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(1.0f, 0.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(1.0f, 1.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(1.0f, 2.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
	};
};