#include "GameManager.h"

bool GameManager::mNewGame = false;
int GameManager::mNewGameClasses[4];
std::string GameManager::mNewGameNames[4];

bool GameManager::mLoadedGame = false;
GameManager::SaveData GameManager::mSaveData;

std::string GameManager::mSceneName = "";

bool GameManager::mIsOverworld = false;
bool GameManager::mIsTown = false;
bool GameManager::mIsIndoors = false;

bool GameManager::mReturnToOverworld = false;
int GameManager::mSceneEntranceIndex = -1;
Vec2 GameManager::mCurrentCharacterPositions[4];
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
	int partyIndex = 0;

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

				PlayerManager::SetCharacterAttribites(partyIndex, attributes);
				partyIndex++;
			}
		}
		else if (type == "CharacterWeapons")
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterWeapon(i, index);
			}
		}
		else if (type == "CharacterShields")
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterShield(i, index);
			}
		}
		else if (type == "CharacterArmourHead")
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterArmourHead(i, index);
			}
		}
		else if (type == "CharacterArmourChest")
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterArmourChest(i, index);
			}
		}
		else if (type == "CharacterArmourArms")
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterArmourArms(i, index);
			}
		}
		else if (type == "CharacterArmourLegs")
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterArmourLegs(i, index);
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
		else if (type == "InventoryShields")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::AddShieldToInventory(Shield(type));
			}
		}
		else if (type == "InventoryArmourHead")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::AddArmourHeadToInventory(Armour(type));
			}
		}
		else if (type == "InventoryArmourChest")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::AddArmourChestToInventory(Armour(type));
			}
			}
		else if (type == "InventoryArmourArms")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::AddArmourArmsToInventory(Armour(type));
			}
		}
		else if (type == "InventoryArmourLegs")
		{
			while (gameSaveInFile >> type)
			{
				if (type == "Break") break;

				PlayerManager::AddArmourLegsToInventory(Armour(type));
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
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << mCurrentCharacterPositions[i].x << ' ' << mCurrentCharacterPositions[i].y << std::endl;
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

			gameSaveOutFile << attributes.characterName << ' '
			<< attributes.characterClass << ' '
			<< attributes.level << ' '
			<< attributes.health << ' ' << attributes.healthMax << ' '
			<< attributes.magic << ' ' << attributes.magicMax << ' '
			<< attributes.strength << ' '
			<< attributes.defense << ' '
			<< attributes.intelligence << ' '
			<< attributes.speed << ' '
			<< attributes.skill << ' '
			<< attributes.luck << ' '
			<< attributes.exp << std::endl << std::endl;
		}

		gameSaveOutFile << "CharacterWeapons" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterWeapon(i) << ' ';
		}
		gameSaveOutFile << std::endl << std::endl;

		gameSaveOutFile << "CharacterShield" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterShield(i) << ' ';
		}
		gameSaveOutFile <<std::endl;

		gameSaveOutFile << "CharacterArmourHead" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterArmourHead(i) << ' ';
		}
		gameSaveOutFile <<std::endl;

		gameSaveOutFile << "CharacterArmourChest" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterArmourChest(i) << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "CharacterArmourArms" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterArmourArms(i) << ' ';
		}
		gameSaveOutFile << std::endl;

		gameSaveOutFile << "CharacterArmourLegs" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterArmourLegs(i) << ' ';
		}
		gameSaveOutFile << std::endl << std::endl;

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
		gameSaveOutFile << "Break" << std::endl << std::endl;

		gameSaveOutFile << "InventoryWeapons ";
		for (int i = 0; i < PlayerManager::GetInventoryWeapons().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryWeapons()[i].mName << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "InventoryShields ";
		for (int i = 0; i < PlayerManager::GetInventoryShields().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryShields()[i].mName << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "InventoryArmourHead ";
		for (int i = 0; i < PlayerManager::GetInventoryArmourHead().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryArmourHead()[i].mName << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "InventoryArmourChest ";
		for (int i = 0; i < PlayerManager::GetInventoryArmourChest().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryArmourChest()[i].mName << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "InventoryArmourArms ";
		for (int i = 0; i < PlayerManager::GetInventoryArmourArms().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryArmourArms()[i].mName << ' ';
		}
		gameSaveOutFile << "Break" << std::endl;

		gameSaveOutFile << "InventoryArmourLegs ";
		for (int i = 0; i < PlayerManager::GetInventoryArmourLegs().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryArmourLegs()[i].mName << ' ';
		}
		gameSaveOutFile << "Break" << std::endl << std::endl;
	}
	gameSaveInFile.close();
}