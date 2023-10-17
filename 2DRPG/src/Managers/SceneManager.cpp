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
			GameManager::SetSceneType();
			mCurrentScene = std::make_unique<SceneBattle>(GameManager::GetBattleBackground(), GameManager::GetEnemyEncounters());
			break;
		}
		case OVERWORLD:
		{
			GameManager::SetSceneType(true);
			mCurrentScene = std::make_unique<SceneOverworld>();
			break;
		}
		case TOWN:
		{
			GameManager::SetSceneType(false, true);
			mCurrentScene = std::make_unique<SceneTown>();
			break;
		}
		case TOWN_SHOP:
		{
			GameManager::SetSceneType(false, false, true);
			mCurrentScene = std::make_unique<SceneTownShop>();
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
	mCurrentScene->Render(GraphicsManager::GetCamera());
}

void SceneManager::CurrentSceneShutdown()
{
	mCurrentScene->Shutdown();
}