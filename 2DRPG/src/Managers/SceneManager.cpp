#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::mCurrentScene = nullptr;
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

void SceneManager::LoadScene()
{
	if (mCurrentScene)
	{
		mCurrentScene->Shutdown();
		mCurrentScene.reset();
	}

	switch (mSceneToLoad)
	{
		case OVERWORLD:
		{
			mIsOverworld = true;
			mCurrentScene = std::make_unique<SceneOverworld>();
			break;
		}
		case TOWN:
		{
			mIsOverworld = false;
			mCurrentScene = std::make_unique<SceneTown>();
			break;
		}
	}

	mSceneToLoad = NONE;

	if (mCurrentScene) mCurrentScene->Setup(GraphicsManager::Renderer());
}

void SceneManager::CurrentSceneInput()
{
	mCurrentScene->Input();
}

void SceneManager::CurrentSceneUpdate(const float dt)
{
	mCurrentScene->Update(dt);
}

void SceneManager::CurrentSceneRender()
{
	mCurrentScene->Render(GraphicsManager::Renderer(), GraphicsManager::Camera());
}

void SceneManager::CurrentSceneShutdown()
{
	mCurrentScene->Shutdown();
}