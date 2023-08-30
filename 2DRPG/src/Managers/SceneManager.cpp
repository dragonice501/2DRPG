#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::mCurrentScene = nullptr;
SceneNames SceneManager::mSceneToLoad = OVERWORLD;
int SceneManager::mSceneEntranceIndex = -1;
bool SceneManager::mIsOverworld = true;
ETerrainType SceneManager::mBattleBakgroundType = UNDEFINED;
std::vector<EnemyEncounter> SceneManager::mEnemyEncounters;
bool SceneManager::mReturnToOverworld = false;
Vec2 SceneManager::mPreviousOverworldPosition = Vec2(0.0f);
Vec2 SceneManager::mPreviousDirection = Vec2(0.0f);

void SceneManager::SetSceneToLoad(const SceneNames sceneToLoad, const int entranceIndex, bool returnToOverworld,
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

	switch (mSceneToLoad)
	{
		case BATTLE:
		{
			mIsOverworld = false;
			mCurrentScene = std::make_unique<SceneBattle>(mBattleBakgroundType, mEnemyEncounters);
			break;
		}
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