#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::mCurrentScene = nullptr;

SceneName SceneManager::mSceneToLoad = OVERWORLD;
int SceneManager::mSceneEntranceIndex = -1;

bool SceneManager::mIsOverworld = true;
ETerrainType SceneManager::mBattleBakgroundType = UNDEFINED;
std::vector<EnemyEncounter> SceneManager::mEnemyEncounters;

bool SceneManager::mReturnToOverworld = false;
std::vector<Vec2> SceneManager::mPreviousOverworldPositions;
std::vector<Vec2> SceneManager::mPreviousDirections;

void SceneManager::SetSceneToLoad(const SceneName sceneToLoad, const int entranceIndex, bool returnToOverworld,
	ETerrainType battleBackgroundType, const std::vector<EnemyEncounter>& enemyEncounters)
{
	mSceneToLoad = sceneToLoad;
	mSceneEntranceIndex = entranceIndex;
	mBattleBakgroundType = battleBackgroundType;
	mEnemyEncounters = enemyEncounters;
	mReturnToOverworld = returnToOverworld;
}

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