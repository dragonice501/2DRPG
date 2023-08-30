#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneBattle.h"
#include "../Scenes/SceneOverworld.h"
#include "../Scenes/SceneTown.h"

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
	inline static Vec2 GetPreviousOverworldPosition() { return mPreviousOverworldPosition; }
	inline static Vec2 GetPreviousDirection() { return mPreviousDirection; }

	inline static void SetPreviousOverworldPosition(const Vec2& position) { mPreviousOverworldPosition = position; }
	inline static void SetPreviousDirection(const Vec2& direction) { mPreviousDirection = direction; }

	static bool SceneReadyToLoad();
	static void SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex, ETerrainType battleBackgroundType = UNDEFINED, bool returnToOverworld = false);

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
	static bool mReturnToOverworld;
	static Vec2 mPreviousOverworldPosition;
	static Vec2 mPreviousDirection;
};