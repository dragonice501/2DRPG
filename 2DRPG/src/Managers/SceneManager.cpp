#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::currentScene = nullptr;
SceneNames SceneManager::mSceneToLoad = OVERWORLD;
int SceneManager::mSceneEntranceIndex = -1;
bool SceneManager::mIsOverworld = true;

bool SceneManager::SceneReadyToLoad()
{
	return mSceneToLoad != NONE;
}

void SceneManager::SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex)
{
	mSceneToLoad = sceneToLoad;
	mSceneEntranceIndex = entranceIndex;
}

void SceneManager::LoadScene(SDL_Renderer* renderer)
{
	if (currentScene)
	{
		currentScene->Shutdown();
		currentScene.reset();
	}

	switch (mSceneToLoad)
	{
		case OVERWORLD:
		{
			mIsOverworld = true;
			currentScene = std::make_unique<SceneOverworld>();
			break;
		}
		case TOWN:
		{
			mIsOverworld = false;
			currentScene = std::make_unique<SceneTown>();
			break;
		}
	}

	mSceneToLoad = NONE;

	if (currentScene) currentScene->Setup(renderer);
}

void SceneManager::CurrentSceneInput()
{
	currentScene->Input();
}

void SceneManager::CurrentSceneUpdate(const float dt)
{
	currentScene->Update(dt);
}

void SceneManager::CurrentSceneRender(SDL_Renderer* renderer)
{
	currentScene->Render(renderer, Engine::Camera());
}

void SceneManager::CurrentSceneShutdown()
{
	currentScene->Shutdown();
}