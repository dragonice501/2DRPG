#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneBattle.h"
#include "../Scenes/SceneOverworld.h"
#include "../Scenes/SceneTown.h"

#include "../Objects/EnemyEncounter.h"

#include "../Managers/GraphicsManager.h"

#include "../Utils/Utils.h"

#include <memory>

class SceneManager
{
public:
	static int GetSceneEntranceIndex() { return mSceneEntranceIndex; }
	static bool GetIsOverworld() { return mIsOverworld; }

	inline static bool CurrentScene() { return mCurrentScene != nullptr; }
	inline static bool ReturnToOverworld() { return mReturnToOverworld; }
	inline static Vec2 GetPreviousOverworldPosition(const int index) { return mPreviousOverworldPositions[index]; }
	inline static Vec2 GetPreviousDirection(const int index) { return mPreviousDirections[index]; }

	inline static void ClearPositionsAndDirections() { mPreviousOverworldPositions.clear(); mPreviousDirections.clear(); }
	inline static void SetPreviousOverworldPosition(const Vec2& position) { mPreviousOverworldPositions.push_back(position); }
	inline static void SetPreviousDirection(const Vec2& direction) { mPreviousDirections.push_back(direction); }

	static inline const bool SceneReadyToLoad() { return mSceneToLoad != NONE; }
	static void SetSceneToLoad(
		const SceneNames sceneToLoad, const int entranceIndex, bool returnToOverworld = false,
		ETerrainType battleBackgroundType = UNDEFINED, const std::vector<EnemyEncounter>& enemyEncounters = std::vector<EnemyEncounter>());

	static void LoadScene();

	static void CurrentSceneInput();
	static void CurrentSceneUpdate(const float dt);
	static void CurrentSceneRender();

	static void CurrentSceneShutdown();

private:
	SceneManager() {};
	~SceneManager() {};

	static std::unique_ptr<Scene> mCurrentScene;

	static SceneNames mSceneToLoad;
	static int mSceneEntranceIndex;

	static bool mIsOverworld;
	static ETerrainType mBattleBakgroundType;
	static std::vector<EnemyEncounter> mEnemyEncounters;

	static bool mReturnToOverworld;
	static std::vector<Vec2> mPreviousOverworldPositions;
	static std::vector<Vec2> mPreviousDirections;
};