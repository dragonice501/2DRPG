#include "GameManager.h"

bool GameManager::mLoadedGame = false;
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

void GameManager::LoadGameSave()
{
	mLoadedGame = true;

	std::string type;
	std::string gameSavePath = "./assets/files/gamesave.txt";
	std::ifstream gameSaveInFile(gameSavePath);
	while (gameSaveInFile >> type)
	{
		if (type == "LevelName") gameSaveInFile >> mSceneToLoad;
		else if (type == "Gold") gameSaveInFile >> PlayerManager::mPartyGold;
		else if (type == "CharacterPositions")
		{
			for (int i = 0; i < 4; i++)
			{
				Vec2 position;
				gameSaveInFile >> position.x >> position.y;

				mPreviousCharacterPositions.push_back(position);
			}
		}
		else if (type == "CharacterDirections")
		{
			for (int i = 0; i < 4; i++)
			{
				Vec2 direction;
				gameSaveInFile >> direction.x >> direction.y;

				mPreviousCharacterDirections.push_back(direction);
			}
		}
		else if (type == "Characters")
		{
			for(int i = 0; i < 4; i++)
			{
				CharacterAttributes attributes;

				gameSaveInFile >> attributes.characterName;

				int characterClass;
				gameSaveInFile >> characterClass;
				attributes.characterClass = static_cast<ECharacterClass>(characterClass);

				gameSaveInFile >> attributes.level;

				attributes.expNextLevel = PlayerManager::CalcLevelUpExp(attributes.level);

				gameSaveInFile >> attributes.health;
				gameSaveInFile >> attributes.healthMax;
				gameSaveInFile >> attributes.magic;
				gameSaveInFile >> attributes.magicMax;
				gameSaveInFile >> attributes.strength;
				gameSaveInFile >> attributes.defense;
				gameSaveInFile >> attributes.intelligence;
				gameSaveInFile >> attributes.speed;
				gameSaveInFile >> attributes.skill;
				gameSaveInFile >> attributes.luck;
				gameSaveInFile >> attributes.exp;

				PlayerManager::AddCharacterAttribites(attributes);
			}
		}
		else if (type == "CharacterWeapons")
		{
			for (int i = 0; i < 4; i++)
			{
				int weaponIndex;
				gameSaveInFile >> weaponIndex;
				PlayerManager::SetCharacterWeapon(i, weaponIndex);
			}
		}
		else if (type == "PeopleKeywords")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::LearnNewPeopleKeyword(type);
			}
		}
		else if (type == "PlacesKeywords")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::LearnNewPlaceKeyword(type);
			}
		}
		else if (type == "MysteryKeywords")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::LearnNewMysteryKeyword(type);
			}
		}
		else if (type == "BestiaryKeywords")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::LearnNewBestiaryKeyword(type);
			}
		}
		else if (type == "InventoryWeapons")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::AddWeaponToInventory(Weapon(type));
			}
		}
	}
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

		gameSaveOutFile << "CharacterPositions" << std::endl;
		for (int i = 0; i < mPreviousCharacterPositions.size(); i++)
		{
			gameSaveOutFile << mPreviousCharacterPositions[i].x << ' ' << mPreviousCharacterPositions[i].y << std::endl;
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "CharacterDirections" << std::endl;
		for (int i = 0; i < mPreviousCharacterDirections.size(); i++)
		{
			gameSaveOutFile << mPreviousCharacterDirections[i].x << ' ' << mPreviousCharacterDirections[i].y << std::endl;
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "Characters" << std::endl;
		for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
		{
			CharacterAttributes& attributes = PlayerManager::GetCharacterAttributes()[i];

			gameSaveOutFile << attributes.characterName << std::endl;
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

		gameSaveOutFile << "CharacterWeapons" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterWeapon(i) << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "PeopleKeywords ";
		for (int i = 0; i < PlayerManager::GetPeopleKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetPeopleKeywords()[i] << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "PlacesKeywords ";
		for (int i = 0; i < PlayerManager::GetPlacesKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetPlacesKeywords()[i] << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "MysteryKeywords ";
		for (int i = 0; i < PlayerManager::GetMysteryKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetMysteryKeywords()[i] << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "BestiaryKeywords ";
		for (int i = 0; i < PlayerManager::GetBestiaryKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetBestiaryKeywords()[i] << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "InventoryWeapons ";
		for (int i = 0; i < PlayerManager::GetInventoryWeapons().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryWeapons()[i].mName << ' ';
		}
		gameSaveOutFile << std::endl;
	}
	gameSaveInFile.close();
}