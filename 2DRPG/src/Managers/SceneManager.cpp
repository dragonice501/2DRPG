#include "SceneManager.h"

int SceneManager::mSceneEntranceIndex = -1;
bool SceneManager::mIsOverworld = true;

SceneManager& SceneManager::Instance()
{
	static SceneManager* instance = new SceneManager();
	return *instance;
}

bool SceneManager::SceneReadyToLoad() const
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
	if (currentSceneRef)
	{
		currentSceneRef->Shutdown();
		currentSceneRef.reset();
	}

	switch (mSceneToLoad)
	{
		case OVERWORLD:
		{
			mIsOverworld = true;
			currentSceneRef = std::make_unique<SceneOverworld>();
			break;
		}
		case TOWN:
		{
			mIsOverworld = false;
			currentSceneRef = std::make_unique<SceneTown>();
			break;
		}
	}

	mSceneToLoad = NONE;

	if (currentSceneRef) currentSceneRef->Setup(renderer);
}

void SceneManager::CurrentSceneInput()
{
	currentSceneRef->Input();
}

void SceneManager::CurrentSceneUpdate(const float dt)
{
	currentSceneRef->Update(dt);
}

void SceneManager::CurrentSceneRender(SDL_Renderer* renderer)
{
	currentSceneRef->Render(renderer, Engine::Camera());
}

void SceneManager::CurrentSceneShutdown()
{
	currentSceneRef->Shutdown();
}