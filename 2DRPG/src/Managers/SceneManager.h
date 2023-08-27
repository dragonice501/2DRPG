#pragma once

#include "../Scenes/Scene.h"
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

	static bool SceneReadyToLoad();
	static void SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex);

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
};