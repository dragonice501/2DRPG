#include "SceneManager.h"

SceneManager& SceneManager::Instance()
{
	static SceneManager* instance = new SceneManager();
	return *instance;
}

bool SceneManager::SceneReadyToLoad() const
{
	return mSceneToLoad != NONE;
}

void SceneManager::SetSceneToLoad(const SceneNames sceneToLoad)
{
	mSceneToLoad = sceneToLoad;
}

void SceneManager::LoadScene(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
	if (currentScene)
	{
		currentScene->Shutdown(registry, assetStore, renderer);
		currentScene.reset();
	}

	switch (mSceneToLoad)
	{
		case OVERWORLD:
		{
			currentScene = std::make_unique<SceneTest>();
			break;
		}
		case TOWN:
		{
			currentScene = std::make_unique<SceneTown>();
			break;
		}
	}

	mSceneToLoad = NONE;

	if (currentScene) currentScene->Setup(registry, assetStore, renderer);
}

void SceneManager::CurrentSceneInput(std::unique_ptr<EventBus>& eventBus)
{
	currentScene->Input(eventBus);
}

void SceneManager::CurrentSceneUpdate(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt)
{
	currentScene->Update(registry, eventBus, dt);
}

void SceneManager::CurrentSceneDraw(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
	currentScene->Render(registry, assetStore, renderer);
}