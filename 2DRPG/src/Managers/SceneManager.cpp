#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::mCurrentScene = nullptr;

void SceneManager::LoadScene()
{
	if (mCurrentScene)
	{
		mCurrentScene->Shutdown();
		mCurrentScene.reset();
	}

	if (GameManager::GetSceneToLoad() == "Battle")
	{
		GameManager::SetSceneType();
		mCurrentScene = std::make_unique<SceneBattle>(GameManager::GetBattleBackground(), GameManager::GetEnemyEncounters());
	}
	else if (GameManager::GetSceneToLoad() == "Overworld")
	{
		GameManager::SetSceneType(true);
		mCurrentScene = std::make_unique<SceneOverworld>();
	}
	else if (GameManager::GetSceneToLoad() == "Town")
	{
		GameManager::SetSceneType(false, true);
		mCurrentScene = std::make_unique<SceneTown>();
	}
	else if (GameManager::GetSceneToLoad() == "TownShop")
	{
		GameManager::SetSceneType(false, false, true);
		mCurrentScene = std::make_unique<SceneTownShop>();
	}

	GameManager::SetSceneName(GameManager::GetSceneToLoad());
	GameManager::SetSceneToLoad("None");

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