#pragma once

#include "Scene.h"
#include "../Utils/Utils.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/EnemyEncounter.h"
#include "../GameObjects/ActorBattle.h"
#include "../GameObjects/CharacterBattle.h"
#include "../GameObjects/EnemyBattle.h"

#include "../Graphics/Font.h"

#include "../Managers/AssetManager.h"
#include "../Managers/SceneManager.h"
#include "../Managers/PlayerManager.h"

#include "../UI/MenuBattle.h"
#include "../UI/UIPanel.h"

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

	void SetPlayerIndex();
	void SelectFirstEnemy();
	bool SelectEnemy(int index);
	bool SearchForEnemyUp(int index);
	bool SearchForEnemyDown(int index);
	bool SearchForEnemyLeft(int index);
	bool SearchForEnemyRight(int index);
	void AcceptEnemyTarget(int index);

	void SetEnemyAttackTarget();

	void Render(static SDL_Rect& camera);
	void DrawBattleMenu(SDL_Rect& rect);
	void DrawCursor();
	void DrawBattleEvent(SDL_Rect& rect, const std::string& eventString);

private:
	std::string mBackgroundImageName;

	std::map<std::string, SpriteComponent> mBattleIconsMap;

	std::map<std::string, Enemy> mEnemyMap;
	std::vector<Enemy> mEnemies;
	
	EBattleState mBattleState = BS_SELECTING_ACTION;

	std::vector<CharacterBattle> mPlayerCharacters;
	std::vector<EnemyEncounter> mEnemyEncounters;

	std::vector<ActorBattle*> mBattleTurns;
	std::vector<CharacterBattle*> mBattleCharacters;
	std::vector<EnemyBattle*> mBattleEnemies;

	int mTurnIndex = 0;

	int mBattleMenuIndex = 0;
	int mBattleMenuIndexOptions = 4;

	MenuBattle mBattleMenu;

	int mSelectedCharacterIndex = 0;
	int mBattleSelectedEnemyIndex = 0;

	float mTurnTime = 1.5f;
	float mTurnTimeRemaining = mTurnTime;
	float mBattleEventTime = 2.0f;
	float mBattleEventTimeRemaining = mBattleEventTime;

	int mDamageDealt = 0;
	int mEnemyTargetIndex = 0;
	int mCurrentPlayerIndex = 0;

	int mBattleGoldPool = 0;
	int mBattleExpPool = 0;
	int mLevelUpIndex = 0;

	bool mStatArray[8];
	int mStatIndex = 0;

	std::vector<Vec2> mPlayerCharacterPositions =
	{
		Vec2(GraphicsManager::WindowWidth() * 0.7f, GraphicsManager::WindowWidth() * 0.1f),
		Vec2(GraphicsManager::WindowWidth() * 0.725f, GraphicsManager::WindowWidth() * 0.175f),
		Vec2(GraphicsManager::WindowWidth() * 0.75f, GraphicsManager::WindowWidth() * 0.25f),
		Vec2(GraphicsManager::WindowWidth() * 0.775f, GraphicsManager::WindowWidth() * 0.325f)
	};

	std::vector<Vec2> mSmallEnemyPositions =
	{
		Vec2(GraphicsManager::WindowWidth() * 0.05f, GraphicsManager::WindowWidth() * 0.125f),
		Vec2(GraphicsManager::WindowWidth() * 0.05f, GraphicsManager::WindowWidth() * 0.125f) + Vec2(0.0f, GraphicsManager::WindowWidth() * 0.125f),
		Vec2(GraphicsManager::WindowWidth() * 0.05f, GraphicsManager::WindowWidth() * 0.125f) + Vec2(0.0f, GraphicsManager::WindowWidth() * 0.25f),
		Vec2(GraphicsManager::WindowWidth() * 0.05f, GraphicsManager::WindowWidth() * 0.125f) + Vec2(GraphicsManager::WindowWidth() * 0.15f, 0.0f),
		Vec2(GraphicsManager::WindowWidth() * 0.05f, GraphicsManager::WindowWidth() * 0.125f) + Vec2(GraphicsManager::WindowWidth() * 0.15f, GraphicsManager::WindowWidth() * 0.125f),
		Vec2(GraphicsManager::WindowWidth() * 0.05f, GraphicsManager::WindowWidth() * 0.125f) + Vec2(GraphicsManager::WindowWidth() * 0.15f, GraphicsManager::WindowWidth() * 0.25f)
	};
};