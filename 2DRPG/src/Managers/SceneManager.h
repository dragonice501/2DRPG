#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneOverworld.h"
#include "../Scenes/SceneTown.h"

#include "../Utils/Utils.h"

#include <memory>

class SceneManager
{
public:
	static SceneManager& Instance();

	static int GetSceneEntranceIndex() { return mSceneEntranceIndex; }
	static bool GetIsOverworld() { return mIsOverworld; }

	bool CurrentScene() { return currentScene != nullptr; }

	bool SceneReadyToLoad() const;
	void SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex);

	void LoadScene(SDL_Renderer* renderer);

	void CurrentSceneInput();
	void CurrentSceneUpdate(const float dt);
	void CurrentSceneRender(SDL_Renderer* renderer);

	void CurrentSceneShutdown();

private:
	SceneManager() {};

	std::unique_ptr<Scene> currentScene = nullptr;

	SceneNames mSceneToLoad = NONE;
	static int mSceneEntranceIndex;
	static bool mIsOverworld;
};