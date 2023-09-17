#include "GameManager.h"

bool GameManager::mIsOverworld = true;
bool GameManager::mReturnToOverworld = false;
int GameManager::mSceneEntranceIndex = -1;
std::vector<Vec2> GameManager::mPreviousOverworldPositions;
std::vector<Vec2> GameManager::mPreviousDirections;
SceneName GameManager::mSceneToLoad = OVERWORLD;

ETerrainType GameManager::mBattleBackgroundType = UNDEFINED;
std::vector<EnemyEncounter> GameManager::mEnemyEncounters;

void GameManager::SetSceneToLoad(const SceneName sceneToLoad, const int entranceIndex, bool returnToOverworld,
	ETerrainType battleBackgroundType, const std::vector<EnemyEncounter>& enemyEncounters)
{
	mSceneToLoad = sceneToLoad;
	mSceneEntranceIndex = entranceIndex;
	mBattleBackgroundType = battleBackgroundType;
	mEnemyEncounters = enemyEncounters;
	mReturnToOverworld = returnToOverworld;
}