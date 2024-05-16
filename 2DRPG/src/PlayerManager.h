#pragma once

#include "Armour.h"
#include "Shield.h"
#include "Weapon.h"

#include "AssetManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"

#include "Components.h"

#include <vector>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

class PlayerManager
{
public:
	static void LoadCharacters();
	static void SaveCharacters();

	static void LoadNewGameDefaultCharacters();
	static void LoadClassStartingAttributes(int partyIndex, const std::string& className);

	static std::vector<CharacterAttributes>& GetCharacterAttributes() { return mCharacterAttributes; }
	static const int* GetCharacterWeapons() { return mCharacterWeaponIndeces; }
	static const int GetCharacterWeapon(const int index) { return mCharacterWeaponIndeces[index]; }
	static const int GetCharacterShield(const int index) { return mCharacterShieldIndeces[index]; }
	static const int GetCharacterArmourHead(const int index) { return mCharacterArmourHeadIndeces[index]; }
	static const int GetCharacterArmourBody(const int index) { return mCharacterArmourBodyIndeces[index]; }

	static void SetCharacterAttribites(const int partyIndex, const CharacterAttributes& attributes) { mCharacterAttributes[partyIndex] = attributes; }
	static void SetCharacterWeapon(const int characterIndex, const int weaponIndex) { mCharacterWeaponIndeces[characterIndex] = weaponIndex; }
	static void SetCharacterShield(const int characterIndex, const int shieldIndex) { mCharacterShieldIndeces[characterIndex] = shieldIndex; }
	static void SetCharacterArmourHead(const int characterIndex, const int headIndex) { mCharacterArmourHeadIndeces[characterIndex] = headIndex; }
	static void SetCharacterArmourBody(const int characterIndex, const int BodyIndex) { mCharacterArmourBodyIndeces[characterIndex] = BodyIndex; }

	static const int& GetPartyGold() { return mPartyGold; }
	static const std::vector<std::string>& GetPeopleKeywords() { return mPeopleKeywords; }
	static const std::vector<std::string>& GetPlacesKeywords() { return mPlacesKeywords; }
	static const std::vector<std::string>& GetMysteryKeywords() { return mMysteryKeywords; }
	static const std::vector<std::string>& GetBestiaryKeywords() { return mBestiaryKeywords; }

	static const std::vector<Weapon>& GetInventoryWeapons() { return mInventoryWeapons; }
	static const std::vector<Shield>& GetInventoryShields() { return mInventoryShields; }
	static const std::vector<Armour>& GetInventoryArmourHead() { return mInventoryArmourHead; }
	static const std::vector<Armour>& GetInventoryArmourBody() { return mInventoryArmourBody; }

	static void LearnNewPeopleKeyword(const std::string& keyword) { mPeopleKeywords.push_back(keyword); }
	static void LearnNewPlaceKeyword(const std::string& keyword) { mPlacesKeywords.push_back(keyword); }
	static void LearnNewMysteryKeyword(const std::string& keyword) { mMysteryKeywords.push_back(keyword); }
	static void LearnNewBestiaryKeyword(const std::string& keyword) { mBestiaryKeywords.push_back(keyword); }

	static void AddWeaponToInventory(const Weapon& newWeapon) { mInventoryWeapons.push_back(newWeapon); }
	static void AddShieldToInventory(const Shield& newShield) { mInventoryShields.push_back(newShield); }
	static void AddArmourHeadToInventory(const Armour& newArmour) { mInventoryArmourHead.push_back(newArmour); }
	static void AddArmourBodyToInventory(const Armour& newArmour) { mInventoryArmourBody.push_back(newArmour); }

	static void SetupCharacters();

	static void AddGold(const int gold) { mPartyGold += gold; }
	static void SubtractGold(const int gold) { mPartyGold -= gold; }
	static int CalcLevelUpExp(int level);
	static bool CheckLevelUp(int& outIndex);
	static CharacterAttributes LevelUp(int characterIndex, bool* outStats);
	static void RemoveAllEquipment(const int characterIndex);
	static int GetPlayerWeaponDamage(const int index);

	static void SwapCharacters(int first, int second);
	static void SwapCharacterInventories(int first, int second);

	static bool CanEquipWeapon(int weaponIndex);
	static bool CanEquipShield(int shieldIndex);
	static bool CanEquipArmourHead(int armourIndex);
	static bool CanEquipArmourBody(int armourIndex);

	static int mPartyGold;
private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
	static int mCharacterWeaponIndeces[4];
	static int mCharacterShieldIndeces[4];
	static int mCharacterArmourHeadIndeces[4];
	static int mCharacterArmourBodyIndeces[4];

	static std::vector<std::string> mPeopleKeywords;
	static std::vector<std::string> mPlacesKeywords;
	static std::vector<std::string> mMysteryKeywords;
	static std::vector<std::string> mBestiaryKeywords;

	static std::vector<Weapon> mInventoryWeapons;
	static std::vector<Shield> mInventoryShields;
	static std::vector<Armour> mInventoryArmourHead;
	static std::vector<Armour> mInventoryArmourBody;

	static int mLevelExpAmounts[];

	static uint8_t mLevelGauranteeStatsDancer[];
	static uint8_t mLevelGauranteeStatsKnight[];
	static uint8_t mLevelGauranteeStatsMage[];
	static uint8_t mLevelGauranteeStatsPaladin[];
};