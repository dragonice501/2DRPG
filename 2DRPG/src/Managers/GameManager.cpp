#include "GameManager.h"

GameManager::SaveData GameManager::mSaveData;

std::string GameManager::mSceneName = "";

bool GameManager::mIsOverworld = false;
bool GameManager::mIsTown = false;
bool GameManager::mIsIndoors = false;

bool GameManager::mReturnToOverworld = false;
int GameManager::mSceneEntranceIndex = -1;
std::vector<Vec2> GameManager::mPreviousCharacterPositions;
std::vector<Vec2> GameManager::mPreviousCharacterDirections;
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
	std::string gameSavePath = "./assets/files/gamesave.txt";
	std::ifstream gameSaveInFile;
	gameSaveInFile.open(gameSavePath);
	if (gameSaveInFile.is_open())
	{
		gameSaveInFile.close();
		std::remove(gameSavePath.c_str());
	}

	std::ofstream gameSaveOutFile;
	gameSaveOutFile.open(gameSavePath);
	if (gameSaveOutFile.is_open())
	{
		gameSaveOutFile << "LevelName " << mSceneName << std::endl << std::endl;

		gameSaveOutFile << "Gold " << PlayerManager::GetPartyGold() << std::endl << std::endl;;

		for (int i = 0; i < mPreviousCharacterPositions.size(); i++)
		{
			gameSaveOutFile << "CharacterPosition " << mPreviousCharacterPositions[i].x << ' ' << mPreviousCharacterPositions[i].y << std::endl;
		}
		gameSaveOutFile << std::endl;

		for (int i = 0; i < mPreviousCharacterDirections.size(); i++)
		{
			gameSaveOutFile << "CharacterDirections " << mPreviousCharacterDirections[i].x << ' ' << mPreviousCharacterDirections[i].y << std::endl;
		}
		gameSaveOutFile << std::endl;

		for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
		{
			CharacterAttributes& attributes = PlayerManager::GetCharacterAttributes()[i];

			gameSaveOutFile << "Character " << attributes.characterName << std::endl;
			gameSaveOutFile << "Class " << attributes.characterClass << std::endl;
			gameSaveOutFile << "Level " << attributes.level << std::endl;
			gameSaveOutFile << "Health " << attributes.health << ' ' << attributes.healthMax << std::endl;
			gameSaveOutFile << "Magic " << attributes.magic << ' ' << attributes.magicMax << std::endl;
			gameSaveOutFile << "Strength " << attributes.strength << std::endl;
			gameSaveOutFile << "Defense " << attributes.defense << std::endl;
			gameSaveOutFile << "Intelligence " << attributes.intelligence << std::endl;
			gameSaveOutFile << "Speed " << attributes.speed << std::endl;
			gameSaveOutFile << "Skill " << attributes.skill << std::endl;
			gameSaveOutFile << "Luck " << attributes.luck << std::endl;
			gameSaveOutFile << "Exp " << attributes.exp << std::endl << std::endl;
		}

		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << "CharacterWeapon " << PlayerManager::GetCharacterWeapon(i) << std::endl;
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "PeopleKeywords ";
		for (int i = 0; i < PlayerManager::GetPeopleKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetPeopleKeywords()[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "PlacesKeywords ";
		for (int i = 0; i < PlayerManager::GetPlacesKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetPlacesKeywords()[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "MysteryKeywords ";
		for (int i = 0; i < PlayerManager::GetMysteryKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetMysteryKeywords()[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "BestiaryKeywords ";
		for (int i = 0; i < PlayerManager::GetBestiaryKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetBestiaryKeywords()[i] << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "InventoryWeapons ";
		for (int i = 0; i < PlayerManager::GetInventoryWeapons().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryWeapons()[i].mName << ' ';
		}
		gameSaveOutFile << std::endl;
	}
	gameSaveInFile.close();
}