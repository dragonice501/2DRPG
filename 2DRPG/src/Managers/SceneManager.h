#pragma once

#include "../Scene/Scene.h"
#include "../Scene/SceneOverworld.h"
#include "../Scene/SceneTown.h"

#include <memory>

class SceneManager
{
public:
	static SceneManager& Instance();

	static int GetSceneEntranceIndex() { return mSceneEntranceIndex; }
	static bool GetIsOverworld() { return mIsOverworld; }

	bool SceneReadyToLoad() const;
	void SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex);

	void LoadScene(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	void CurrentSceneInput(std::unique_ptr<EventBus>& eventBus);

	void CurrentSceneUpdate(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt);

	void CurrentSceneDraw(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

private:
	SceneManager() {};

	std::unique_ptr<Scene> currentScene = nullptr;
	SceneNames mSceneToLoad = NONE;
	static int mSceneEntranceIndex;
	static bool mIsOverworld;
};