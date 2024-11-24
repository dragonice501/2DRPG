#include "GameManager.h"
#include "FileStringConstants.h"

bool GameManager::mNewGame = false;
int GameManager::mNewGameClasses[4];
std::string GameManager::mNewGameNames[4];

bool GameManager::mGameSaveExists = false;

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
	std::string basePath = SDL_GetBasePath();
	std::ifstream gameSaveInFile(basePath + STRING_SAVE_PATH);
	while (gameSaveInFile >> type)
	{
		if (type == STRING_LEVEL_NAME) gameSaveInFile >> mSceneToLoad;
		else if (type == STRING_GOLD) gameSaveInFile >> PlayerManager::mPartyGold;
		else if (type == STRING_CHARACTER_POSITIONS)
		{
			for (int i = 0; i < 4; i++)
			{
				Vec2 position;
				gameSaveInFile >> position.x >> position.y;

				mPreviousCharacterPositions.push_back(position);
			}
		}
		else if (type == STRING_CHARACTER_DIRECTIONS)
		{
			for (int i = 0; i < 4; i++)
			{
				Vec2 direction;
				gameSaveInFile >> direction.x >> direction.y;

				mPreviousCharacterDirections.push_back(direction);
			}
		}
		else if (type == STRING_CHARACTERS)
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

				gameSaveInFile >>
					attributes.health >> attributes.healthMax >> attributes.magic >> attributes.magicMax >> attributes.strength >> 
					attributes.defense  >> attributes.intelligence >> attributes.speed >> attributes.skill >> attributes.luck >> attributes.exp;

				PlayerManager::SetCharacterAttribites(partyIndex, attributes);
				partyIndex++;
			}
		}
		else if (type == STRING_CHARACTER_WEAPONS)
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterWeapon(i, index);
			}
		}
		else if (type == STRING_CHARACTER_SHIELDS)
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterShield(i, index);
			}
		}
		else if (type == STRING_CHARACTER_ARMOUR_HEAD)
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterArmourHead(i, index);
			}
		}
		else if (type == STRING_CHARACTER_ARMOUR_BODY)
		{
			for (int i = 0; i < 4; i++)
			{
				int index;
				gameSaveInFile >> index;
				PlayerManager::SetCharacterArmourBody(i, index);
			}
		}
		else if (type == STRING_PEOPLE_KEYWORDS)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::LearnNewPeopleKeyword(type);
			}
		}
		else if (type == STRING_PLACES_KEYWORDS)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::LearnNewPlaceKeyword(type);
			}
		}
		else if (type == STRING_MYSTERY_KEYWORDS)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::LearnNewMysteryKeyword(type);
			}
		}
		else if (type == STRING_BESTIARY_KEYWORDS)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::LearnNewBestiaryKeyword(type);
			}
		}
		else if (type == STRING_INVENTORY_WEAPONS)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::AddWeaponToInventory(Weapon(type));
			}
		}
		else if (type == STRING_INVENTORY_SHIELDS)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::AddShieldToInventory(Shield(type));
			}
		}
		else if (type == STRING_INVENTORY_ARMOUR_HEAD)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::AddArmourHeadToInventory(Armour(type));
			}
		}
		else if (type == STRING_INVENTORY_ARMOUR_BODY)
		{
			while (gameSaveInFile >> type)
			{
				if (type == STRING_BREAK) break;

				PlayerManager::AddArmourBodyToInventory(Armour(type));
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
	std::string basePath = SDL_GetBasePath();
	std::cout << basePath + STRING_SAVE_PATH << "\n";
	std::ifstream gameSaveInFile;
	gameSaveInFile.open(basePath + STRING_SAVE_PATH);
	if (gameSaveInFile.is_open())
	{
		gameSaveInFile.close();
		std::remove((basePath + STRING_SAVE_PATH).c_str());
		std::cout << "Removed" << "\n";
	}

	std::ofstream gameSaveOutFile;
	gameSaveOutFile.open(basePath + STRING_SAVE_PATH);
	if (gameSaveOutFile.is_open())
	{
		gameSaveOutFile << STRING_LEVEL_NAME << "\n" << mSceneName << "\n" << "\n";

		gameSaveOutFile << STRING_GOLD << "\n" << PlayerManager::GetPartyGold() << "\n" << "\n";

		gameSaveOutFile << STRING_CHARACTER_POSITIONS << "\n";
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << mCurrentCharacterPositions[i].x << ' ' << mCurrentCharacterPositions[i].y << "\n";
		}
		gameSaveOutFile << "\n";

		gameSaveOutFile << STRING_CHARACTER_DIRECTIONS << "\n";
		for (int i = 0; i < mPreviousCharacterDirections.size(); i++)
		{
			gameSaveOutFile << mPreviousCharacterDirections[i].x << ' ' << mPreviousCharacterDirections[i].y << "\n";
			std::cout << mPreviousCharacterDirections[i].x << ' ' << mPreviousCharacterDirections[i].y << "\n";
		}
		gameSaveOutFile << "\n";

		gameSaveOutFile << STRING_CHARACTERS << "\n";
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
			<< attributes.exp << "\n" << "\n";
		}

		gameSaveOutFile << STRING_CHARACTER_WEAPONS << "\n";
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterWeapon(i) << ' ';
		}
		gameSaveOutFile << "\n" << "\n";

		gameSaveOutFile << STRING_CHARACTER_SHIELDS << "\n";
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterShield(i) << ' ';
		}
		gameSaveOutFile <<"\n";

		gameSaveOutFile << STRING_CHARACTER_ARMOUR_HEAD << "\n";
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterArmourHead(i) << ' ';
		}
		gameSaveOutFile <<"\n";

		gameSaveOutFile << STRING_CHARACTER_ARMOUR_BODY << "\n";
		for (int i = 0; i < 4; i++)
		{
			gameSaveOutFile << PlayerManager::GetCharacterArmourBody(i) << ' ';
		}
		gameSaveOutFile << "\n";

		gameSaveOutFile << STRING_PEOPLE_KEYWORDS << ' ';
		for (int i = 0; i < PlayerManager::GetPeopleKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetPeopleKeywords()[i] << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";

		gameSaveOutFile << STRING_PLACES_KEYWORDS << ' ';
		for (int i = 0; i < PlayerManager::GetPlacesKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetPlacesKeywords()[i] << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";

		gameSaveOutFile << STRING_MYSTERY_KEYWORDS << ' ';
		for (int i = 0; i < PlayerManager::GetMysteryKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetMysteryKeywords()[i] << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";

		gameSaveOutFile << STRING_BESTIARY_KEYWORDS << ' ';
		for (int i = 0; i < PlayerManager::GetBestiaryKeywords().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetBestiaryKeywords()[i] << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n" << "\n";

		gameSaveOutFile << STRING_INVENTORY_WEAPONS << ' ';
		for (int i = 0; i < PlayerManager::GetInventoryWeapons().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryWeapons()[i].mName << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";

		gameSaveOutFile << STRING_INVENTORY_SHIELDS << ' ';
		for (int i = 0; i < PlayerManager::GetInventoryShields().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryShields()[i].mName << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";

		gameSaveOutFile << STRING_INVENTORY_ARMOUR_HEAD << ' ';
		for (int i = 0; i < PlayerManager::GetInventoryArmourHead().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryArmourHead()[i].mName << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";

		gameSaveOutFile << STRING_INVENTORY_ARMOUR_BODY << ' ';
		for (int i = 0; i < PlayerManager::GetInventoryArmourBody().size(); i++)
		{
			gameSaveOutFile << PlayerManager::GetInventoryArmourBody()[i].mName << ' ';
		}
		gameSaveOutFile << STRING_BREAK << "\n";
	}
	gameSaveInFile.close();
}

void GameManager::CheckGameSaveExists()
{
	std::string basePath = SDL_GetBasePath();
	std::string gameSavePath = "assets\\saves\\GameSave.txt";
	std::ifstream gameSaveInFile;
	gameSaveInFile.open(basePath + gameSavePath);
	mGameSaveExists = gameSaveInFile.is_open();
}