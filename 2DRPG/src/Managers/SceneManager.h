#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneOverworld.h"
#include "../Scenes/SceneTown.h"

#include "../Utils/Utils.h"

#include <memory>

class SceneManager
{
public:
	static int GetSceneEntranceIndex() { return mSceneEntranceIndex; }
	static bool GetIsOverworld() { return mIsOverworld; }

	static bool CurrentScene() { return currentScene != nullptr; }

	static bool SceneReadyToLoad();
	static void SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex);

	static void LoadScene(SDL_Renderer* renderer);

	static void CurrentSceneInput();
	static void CurrentSceneUpdate(const float dt);
	static void CurrentSceneRender(SDL_Renderer* renderer);

	static void CurrentSceneShutdown();

private:
	SceneManager() {};
	~SceneManager() {};

	static std::unique_ptr<Scene> currentScene;

	static SceneNames mSceneToLoad;
	static int mSceneEntranceIndex;
	static bool mIsOverworld;
};