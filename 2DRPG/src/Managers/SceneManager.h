#pragma once

#include "../Scene/Scene.h"
#include "../Scene/SceneTest.h"

#include <memory>

class SceneManager
{
public:
	static SceneManager& Intance()
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	void LoadScene(SceneNames sceneToLoad, std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
	{
		if (currentScene) currentScene.reset();

		switch (sceneToLoad)
		{
			case OVERWORLD:
			{
				currentScene = std::make_unique<SceneTest>();
				break;
			}
			case TOWN:
			{
				break;
			}
		}

		if (currentScene) currentScene->Setup(registry, assetStore, renderer);
	}

	void CurrentSceneInput(std::unique_ptr<EventBus>& eventBus)
	{
		currentScene->Input(eventBus);
	}

	void CurrentSceneUpdate(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt)
	{
		currentScene->Update(registry, eventBus, dt);
	}

	void CurrentSceneDraw(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
	{
		currentScene->Render(registry, assetStore, renderer);
	}

private:
	SceneManager() {};

	std::unique_ptr<Scene> currentScene;
};