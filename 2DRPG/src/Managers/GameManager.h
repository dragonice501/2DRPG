#pragma once

#include "../Objects/EnemyEncounter.h"

#include "../Managers/GraphicsManager.h"

#include "../Utils/Utils.h"

#include <vector>

class GameManager
{
public:

	inline static bool GetIsOverworld() { return mIsOverworld; }
	inline static bool GetReturnToOverworld() { return mReturnToOverworld; }
	inline static int GetSceneEntranceIndex() { return mSceneEntranceIndex; }
	inline static Vec2 GetPreviousOverworldPosition(const int index) { return mPreviousOverworldPositions[index]; }
	inline static Vec2 GetPreviousDirection(const int index) { return mPreviousDirections[index]; }
	inline static SceneName GetSceneToLoad() { return mSceneToLoad; }
	inline static ETerrainType GetBattleBackground() { return mBattleBackgroundType; }
	inline static std::vector<EnemyEncounter>& GetEnemyEncounters() { return mEnemyEncounters; }

	inline static void SetIsOverworld(const bool isOverworld) { mIsOverworld = isOverworld; }
	inline static void SetSceneToLoad(const SceneName scene) { mSceneToLoad = scene; }
	inline static void ClearPositionsAndDirections() { mPreviousOverworldPositions.clear(); mPreviousDirections.clear(); }
	inline static void SetPreviousOverworldPosition(const Vec2& position) { mPreviousOverworldPositions.push_back(position); }
	inline static void SetPreviousDirection(const Vec2& direction) { mPreviousDirections.push_back(direction); }

	static inline const bool SceneReadyToLoad() { return mSceneToLoad != NONE; }
	static void SetSceneToLoad(
		const SceneName sceneToLoad, const int entranceIndex, bool returnToOverworld = false,
		ETerrainType battleBackgroundType = UNDEFINED, const std::vector<EnemyEncounter>& enemyEncounters = std::vector<EnemyEncounter>());

private:
	static bool mIsOverworld;
	static bool mReturnToOverworld;
	static int mSceneEntranceIndex;
	static std::vector<Vec2> mPreviousOverworldPositions;
	static std::vector<Vec2> mPreviousDirections;
	static SceneName mSceneToLoad;
	
	static ETerrainType mBattleBackgroundType;
	static std::vector<EnemyEncounter> mEnemyEncounters;
};