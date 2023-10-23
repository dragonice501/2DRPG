#pragma once

#include "../Items/Weapon.h"

#include "../Objects/Components.h"
#include "../Objects/EnemyEncounter.h"

#include "../Managers/GraphicsManager.h"
#include "../Managers/PlayerManager.h"
//#include "../Managers/SceneManager.h"

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
	inline static Vec2 GetPreviousOverworldPosition(const int index) { return mPreviousOverworldPositions[index]; }
	inline static Vec2 GetPreviousDirection(const int index) { return mPreviousDirections[index]; }
	inline static const std::string& GetSceneToLoad() { return mSceneToLoad; }
	inline static ETerrainType GetBattleBackground() { return mBattleBackgroundType; }
	inline static std::vector<EnemyEncounter>& GetEnemyEncounters() { return mEnemyEncounters; }

	static void SetSceneName(const std::string& name) { mSceneName = name; }
	static void SetSceneType(const bool isOverworld = false, const bool isTown = false, const bool isIndoors = false);
	inline static void SetSceneToLoad(const std::string& name) { mSceneToLoad = name; }
	inline static void ClearPositionsAndDirections() { mPreviousOverworldPositions.clear(); mPreviousDirections.clear(); }
	inline static void SetPreviousOverworldPosition(const Vec2& position) { mPreviousOverworldPositions.push_back(position); }
	inline static void SetPreviousDirection(const Vec2& direction) { mPreviousDirections.push_back(direction); }

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

	static SaveData mSaveData;

	static std::string mSceneName;

	static bool mIsOverworld;
	static bool mIsTown;
	static bool mIsIndoors;

	static bool mReturnToOverworld;
	static int mSceneEntranceIndex;
	static std::vector<Vec2> mPreviousOverworldPositions;
	static std::vector<Vec2> mPreviousDirections;
	static std::string mSceneToLoad;
	
	static ETerrainType mBattleBackgroundType;
	static std::vector<EnemyEncounter> mEnemyEncounters;
};