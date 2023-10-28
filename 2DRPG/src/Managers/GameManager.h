#pragma once

#include "../Items/Armour.h"
#include "../Items/Shield.h"
#include "../Items/Weapon.h"

#include "../Objects/Components.h"
#include "../Objects/EnemyEncounter.h"

#include "../Managers/GraphicsManager.h"
#include "../Managers/PlayerManager.h"

#include "../Utils/Utils.h"

#include <vector>
#include <fstream>

class GameManager
{
public:

	inline static bool GetIsOverworld() { return mIsOverworld; }
	inline static bool GetIsTown() { return mIsTown; }
	inline static bool GetIsIndoors() { return mIsIndoors; }

	inline static std::string& GetSceneName() { return mSceneName; }
	inline static bool GetReturnToOverworld() { return mReturnToOverworld; }
	inline static int GetSceneEntranceIndex() { return mSceneEntranceIndex; }
	inline static Vec2 GetPreviousCharacterPosition(const int index) { return mPreviousCharacterPositions[index]; }
	inline static Vec2 GetPreviousCharacterDirection(const int index) { return mPreviousCharacterDirections[index]; }
	inline static const std::string& GetSceneToLoad() { return mSceneToLoad; }
	inline static ETerrainType GetBattleBackground() { return mBattleBackgroundType; }
	inline static std::vector<EnemyEncounter>& GetEnemyEncounters() { return mEnemyEncounters; }

	inline static void SetSceneName(const std::string& name) { mSceneName = name; }
	static void SetSceneType(const bool isOverworld = false, const bool isTown = false, const bool isIndoors = false);
	inline static void SetSceneToLoad(const std::string& name) { mSceneToLoad = name; }
	inline static void ClearPositionsAndDirections() { mPreviousCharacterPositions.clear(); mPreviousCharacterDirections.clear(); }
	inline static void SetCurrentCharacterPosition(const int index, const Vec2& position) { mCurrentCharacterPositions[index] = position; }
	inline static void SetPreviousOverworldPosition(const Vec2& position) { mPreviousCharacterPositions.push_back(position); }
	inline static void SetPreviousOverworldDirection(const Vec2& direction) { mPreviousCharacterDirections.push_back(direction); }

	inline static bool LoadedGame() { return mLoadedGame; }
	static void LoadGameSave();
	static inline const bool SceneReadyToLoad() { return mSceneToLoad != "None"; }
	static void SetSceneToLoad(
		const std::string& sceneToLoad, const int entranceIndex, bool returnToOverworld = false,
		ETerrainType battleBackgroundType = UNDEFINED, const std::vector<EnemyEncounter>& enemyEncounters = std::vector<EnemyEncounter>());

	static void SaveGame();

private:
	struct SaveData
	{
		std::string levelName;
		std::vector<Vec2> lastPositions;

		int partyGold;
		std::vector<CharacterAttributes> partyAttributes;
		int characterWeaponIndeces[4];

		std::vector<std::string> peopleKeywords;
		std::vector<std::string> placesKeywords;
		std::vector<std::string> mysteryKeywords;
		std::vector<std::string> bestiaryKeywords;

		std::vector<Weapon> mInventoryWeapons;
	};

	static bool mLoadedGame;
	static SaveData mSaveData;

	static std::string mSceneName;

	static bool mIsOverworld;
	static bool mIsTown;
	static bool mIsIndoors;

	static bool mReturnToOverworld;
	static int mSceneEntranceIndex;
	static Vec2 mCurrentCharacterPositions[4];
	static std::vector<Vec2> mPreviousCharacterPositions;
	static std::vector<Vec2> mPreviousCharacterDirections;
	static std::string mSceneToLoad;
	
	static ETerrainType mBattleBackgroundType;
	static std::vector<EnemyEncounter> mEnemyEncounters;
};