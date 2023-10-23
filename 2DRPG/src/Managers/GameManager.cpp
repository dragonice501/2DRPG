#include "GameManager.h"

GameManager::SaveData GameManager::mSaveData;

std::string GameManager::mSceneName = "";

bool GameManager::mIsOverworld = false;
bool GameManager::mIsTown = false;
bool GameManager::mIsIndoors = false;

bool GameManager::mReturnToOverworld = false;
int GameManager::mSceneEntranceIndex = -1;
std::vector<Vec2> GameManager::mPreviousOverworldPositions;
std::vector<Vec2> GameManager::mPreviousDirections;
std::string GameManager::mSceneToLoad = "None";

ETerrainType GameManager::mBattleBackgroundType = UNDEFINED;
std::vector<EnemyEncounter> GameManager::mEnemyEncounters;

void GameManager::SetSceneType(const bool isOverworld, const bool isTown, const bool isIndoors)
{
	mIsOverworld = isOverworld;
	mIsTown = isTown;
	mIsIndoors = isIndoors;
}

void GameManager::SetSceneToLoad(const std::string& sceneToLoad, const int entranceIndex, bool returnToOverworld,
	ETerrainType battleBackgroundType, const std::vector<EnemyEncounter>& enemyEncounters)
{
	mSceneToLoad = sceneToLoad;
	mSceneEntranceIndex = entranceIndex;
	mBattleBackgroundType = battleBackgroundType;
	mEnemyEncounters = enemyEncounters;
	mReturnToOverworld = returnToOverworld;
}

void GameManager::SaveGame()
{
	mSaveData.levelName = "";

	/*if (static_cast<std::unique_ptr<SceneExploration>&>(SceneManager::GetCurrentScene())
	{

	}*/

	mSaveData.partyGold = PlayerManager::GetPartyGold();
	mSaveData.partyGold = PlayerManager::GetPartyGold();
	mSaveData.partyAttributes = PlayerManager::GetCharacterAttributes();
	mSaveData.mInventoryWeapons = PlayerManager::GetInventoryWeapons();

	mSaveData.peopleKeywords = PlayerManager::GetPeopleKeywords();
	mSaveData.placesKeywords = PlayerManager::GetPlacesKeywords();
	mSaveData.mysteryKeywords = PlayerManager::GetPlacesKeywords();
	mSaveData.bestiaryKeywords = PlayerManager::GetBestiaryKeywords();

	mSaveData.mInventoryWeapons = PlayerManager::GetInventoryWeapons();

	std::string gameSavePath = "./assets/gamesave.txt";
	std::ifstream gameSaveInFile;
	gameSaveInFile.open(gameSavePath);
	if (gameSaveInFile.is_open())
	{
		gameSaveInFile.close();
		std::remove(gameSavePath.c_str());
	}

	std::ofstream gameSaveOutFile;
	gameSaveInFile.open(gameSavePath);
	if (gameSaveInFile.is_open())
	{
		gameSaveOutFile << "LevelName " << mSaveData.levelName << std::endl;

		for (int i = 0; i < mSaveData.lastPositions.size(); i++)
		{
			gameSaveOutFile << "CharacterPosition " << mSaveData.lastPositions[i].x << ' ' << mSaveData.lastPositions[i].y << std::endl;
		}

		gameSaveOutFile << "Gold " << mSaveData.partyGold << std::endl;

		for (int i = 0; i < mSaveData.lastPositions.size(); i++)
		{
			gameSaveOutFile << "Character " << mSaveData.partyAttributes[i].characterName << std::endl;
			gameSaveOutFile << "Class " << mSaveData.partyAttributes[i].characterClass << std::endl;
			gameSaveOutFile << "Level " << mSaveData.partyAttributes[i].level << std::endl;
			gameSaveOutFile << "Health " << mSaveData.partyAttributes[i].health << ' ' << mSaveData.partyAttributes[i].healthMax << std::endl;
			gameSaveOutFile << "Magic " << mSaveData.partyAttributes[i].magic << ' ' << mSaveData.partyAttributes[i].magicMax << std::endl;
			gameSaveOutFile << "Strength " << mSaveData.partyAttributes[i].strength << std::endl;
			gameSaveOutFile << "Defense " << mSaveData.partyAttributes[i].defense << std::endl;
			gameSaveOutFile << "Intelligence " << mSaveData.partyAttributes[i].intelligence << std::endl;
			gameSaveOutFile << "Speed " << mSaveData.partyAttributes[i].speed << std::endl;
			gameSaveOutFile << "Skill " << mSaveData.partyAttributes[i].skill << std::endl;
			gameSaveOutFile << "Luck " << mSaveData.partyAttributes[i].luck << std::endl;
			gameSaveOutFile << "Exp " << mSaveData.partyAttributes[i].exp << std::endl;
		}

		gameSaveOutFile << "PeopleKeywords ";
		for (int i = 0; i < mSaveData.peopleKeywords.size(); i++)
		{
			gameSaveOutFile << mSaveData.peopleKeywords[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "PlacesKeywords ";
		for (int i = 0; i < mSaveData.placesKeywords.size(); i++)
		{
			gameSaveOutFile << mSaveData.placesKeywords[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "MysteryKeywords ";
		for (int i = 0; i < mSaveData.mysteryKeywords.size(); i++)
		{
			gameSaveOutFile << mSaveData.mysteryKeywords[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "BestiaryKeywords ";
		for (int i = 0; i < mSaveData.bestiaryKeywords.size(); i++)
		{
			gameSaveOutFile << mSaveData.bestiaryKeywords[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "InventoryWeapons ";
		for (int i = 0; i < mSaveData.mInventoryWeapons.size(); i++)
		{
			gameSaveOutFile << mSaveData.mInventoryWeapons[i].mName;
		}
		gameSaveOutFile << std::endl;
	}
	gameSaveInFile.close();
}