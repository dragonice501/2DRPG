#pragma once

#include "../Items/Armour.h"
#include "../Items/Shield.h"
#include "../Items/Weapon.h"

#include "../Managers/AssetManager.h"
#include "../Managers/GameManager.h"
#include "../Managers/GraphicsManager.h"

#include "../Objects/Components.h"

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
	static const int GetCharacterArmourChest(const int index) { return mCharacterArmourChestIndeces[index]; }
	static const int GetCharacterArmourArms(const int index) { return mCharacterArmourArmsIndeces[index]; }
	static const int GetCharacterArmourLegs(const int index) { return mCharacterArmourLegsIndeces[index]; }

	static void AddCharacterAttribites(const CharacterAttributes& attributes) { mCharacterAttributes.push_back(attributes); }
	static void SetCharacterWeapon(const int characterIndex, const int weaponIndex) { mCharacterWeaponIndeces[characterIndex] = weaponIndex; }
	static void SetCharacterShield(const int characterIndex, const int shieldIndex) { mCharacterShieldIndeces[characterIndex] = shieldIndex; }
	static void SetCharacterArmourHead(const int characterIndex, const int headIndex) { mCharacterArmourHeadIndeces[characterIndex] = headIndex; }
	static void SetCharacterArmourChest(const int characterIndex, const int chestIndex) { mCharacterArmourChestIndeces[characterIndex] = chestIndex; }
	static void SetCharacterArmourArms(const int characterIndex, const int armsIndex) { mCharacterArmourArmsIndeces[characterIndex] = armsIndex; }
	static void SetCharacterArmourLegs(const int characterIndex, const int legsIndex) { mCharacterArmourLegsIndeces[characterIndex] = legsIndex; }

	static const int& GetPartyGold() { return mPartyGold; }
	static const std::vector<std::string>& GetPeopleKeywords() { return mPeopleKeywords; }
	static const std::vector<std::string>& GetPlacesKeywords() { return mPlacesKeywords; }
	static const std::vector<std::string>& GetMysteryKeywords() { return mMysteryKeywords; }
	static const std::vector<std::string>& GetBestiaryKeywords() { return mBestiaryKeywords; }

	static const std::vector<Weapon>& GetInventoryWeapons() { return mInventoryWeapons; }
	static const std::vector<Shield>& GetInventoryShields() { return mInventoryShields; }
	static const std::vector<Armour>& GetInventoryArmourHead() { return mInventoryArmourHead; }
	static const std::vector<Armour>& GetInventoryArmourChest() { return mInventoryArmourChest; }
	static const std::vector<Armour>& GetInventoryArmourArms() { return mInventoryArmourArms; }
	static const std::vector<Armour>& GetInventoryArmourLegs() { return mInventoryArmourLegs; }

	static void LearnNewPeopleKeyword(const std::string& keyword) { mPeopleKeywords.push_back(keyword); }
	static void LearnNewPlaceKeyword(const std::string& keyword) { mPlacesKeywords.push_back(keyword); }
	static void LearnNewMysteryKeyword(const std::string& keyword) { mMysteryKeywords.push_back(keyword); }
	static void LearnNewBestiaryKeyword(const std::string& keyword) { mBestiaryKeywords.push_back(keyword); }

	static void AddWeaponToInventory(const Weapon& newWeapon) { mInventoryWeapons.push_back(newWeapon); }
	static void AddShieldToInventory(const Shield& newShield) { mInventoryShields.push_back(newShield); }
	static void AddArmourHeadToInventory(const Armour& newArmour) { mInventoryArmourHead.push_back(newArmour); }
	static void AddArmourChestToInventory(const Armour& newArmour) { mInventoryArmourChest.push_back(newArmour); }
	static void AddArmourArmsToInventory(const Armour& newArmour) { mInventoryArmourArms.push_back(newArmour); }
	static void AddArmourLegsToInventory(const Armour& newArmour) { mInventoryArmourLegs.push_back(newArmour); }

	static void SetupCharacters();

	static void AddGold(const int gold) { mPartyGold += gold; }
	static void SubtractGold(const int gold) { mPartyGold -= gold; }
	static int CalcLevelUpExp(int level);
	static bool CheckLevelUp(int& outIndex);
	static CharacterAttributes LevelUp(int characterIndex);
	static void RemoveAllEquipment(const int characterIndex);
	static int GetPlayerWeaponDamage(const int index);

	static void SwapCharacters(int first, int second);
	static void SwapCharacterInventories(int first, int second);

	static bool CanEquipWeapon(int weaponIndex);
	static bool CanEquipShield(int shieldIndex);
	static bool CanEquipArmourHead(int armourIndex);
	static bool CanEquipArmourChest(int armourIndex);
	static bool CanEquipArmourArms(int armourIndex);
	static bool CanEquipArmourLegs(int armourIndex);

	static int mPartyGold;
private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
	static int mCharacterWeaponIndeces[4];
	static int mCharacterShieldIndeces[4];
	static int mCharacterArmourHeadIndeces[4];
	static int mCharacterArmourChestIndeces[4];
	static int mCharacterArmourArmsIndeces[4];
	static int mCharacterArmourLegsIndeces[4];

	static std::vector<std::string> mPeopleKeywords;
	static std::vector<std::string> mPlacesKeywords;
	static std::vector<std::string> mMysteryKeywords;
	static std::vector<std::string> mBestiaryKeywords;

	static std::vector<Weapon> mInventoryWeapons;
	static std::vector<Shield> mInventoryShields;
	static std::vector<Armour> mInventoryArmourHead;
	static std::vector<Armour> mInventoryArmourChest;
	static std::vector<Armour> mInventoryArmourArms;
	static std::vector<Armour> mInventoryArmourLegs;

	static int mLevelExpAmounts[];

	static uint8_t mLevelGauranteeStats[];
};