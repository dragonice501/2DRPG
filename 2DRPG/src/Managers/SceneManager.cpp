#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::mCurrentScene = nullptr;

void SceneManager::LoadScene()
{
	if (mCurrentScene)
	{
		mCurrentScene->Shutdown();
		mCurrentScene.reset();
	}

	switch (GameManager::GetSceneToLoad())
	{
		case BATTLE:
		{
			GameManager::SetIsOverworld(false);
			mCurrentScene = std::make_unique<SceneBattle>(GameManager::GetBattleBackground(), GameManager::GetEnemyEncounters());
			break;
		}
		case OVERWORLD:
		{
			GameManager::SetIsOverworld(true);
			mCurrentScene = std::make_unique<SceneOverworld>();
			break;
		}
		case TOWN:
		{
			GameManager::SetIsOverworld(false);
			mCurrentScene = std::make_unique<SceneTown>();
			break;
		}
	}

	GameManager::SetSceneToLoad(NONE);

	if (mCurrentScene) mCurrentScene->Setup(GraphicsManager::GetRenderer());
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
	mCurrentScene->Render(GraphicsManager::GetRenderer(), GraphicsManager::GetCamera());
}

void SceneManager::CurrentSceneShutdown()
{
	mCurrentScene->Shutdown();
}