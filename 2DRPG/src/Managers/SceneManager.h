#pragma once

#include "../Scene/Scene.h"
#include "../Scene/SceneTest.h"
#include "../Scene/SceneTown.h"

#include <memory>

class SceneManager
{
public:
	static SceneManager& Instance();

	bool SceneReadyToLoad() const;
	void SetSceneToLoad(const SceneNames sceneToLoad);

	void LoadScene(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	void CurrentSceneInput(std::unique_ptr<EventBus>& eventBus);

	void CurrentSceneUpdate(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt);

	void CurrentSceneDraw(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

private:
	SceneManager() {};

	std::unique_ptr<Scene> currentScene = nullptr;
	SceneNames mSceneToLoad = NONE;
};