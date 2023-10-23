#pragma once

#include "../Items/Weapon.h"

#include "../Managers/AssetManager.h"
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

	static std::vector<CharacterAttributes>& GetCharacterAttributes() { return mCharacterAttributes; }
	static const int* GetCharacterWeapons() { return mCharacterWeaponIndeces; }
	static const int GetCharacterWeapon(const int index) { return mCharacterWeaponIndeces[index]; }

	static void SetCharacterWeapon(const int characterIndex, const int weaponIndex) { mCharacterWeaponIndeces[characterIndex] = weaponIndex; }

	static const int& GetPartyGold() { return mPartyGold; }
	static const std::vector<std::string>& GetPeopleKeywords() { return mPeopleKeywords; }
	static const std::vector<std::string>& GetPlacesKeywords() { return mPlacesKeywords; }
	static const std::vector<std::string>& GetMysteryKeywords() { return mMysteryKeywords; }
	static const std::vector<std::string>& GetBestiaryKeywords() { return mBestiaryKeywords; }
	static const std::vector<Weapon>& GetInventoryWeapons() { return mInventoryWeapons; }

	static void LearnNewPeopleKeyword(const std::string& keyword) { mPeopleKeywords.push_back(keyword); }
	static void LearnNewPlaceKeyword(const std::string& keyword) { mPlacesKeywords.push_back(keyword); }
	static void LearnNewMysteryKeyword(const std::string& keyword) { mMysteryKeywords.push_back(keyword); }
	static void LearnNewBestiaryKeyword(const std::string& keyword) { mBestiaryKeywords.push_back(keyword); }

	static void AddGold(const int gold) { mPartyGold += gold; }
	static void SubtractGold(const int gold) { mPartyGold -= gold; }
	static int CalcLevelUpExp(int level);
	static bool CheckLevelUp(int& outIndex);
	static CharacterAttributes LevelUp(int characterIndex);

	static void AddWeaponToInventory(const Weapon& newWeapon) { mInventoryWeapons.push_back(newWeapon); }

	static void SwapCharacters(int first, int second);
	static void SwapCharacterInventories(int first, int second);

	static bool CanEquipWeapon(int weaponIndex);

	static int mPartyGold;
private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
	static int mCharacterWeaponIndeces[4];

	static std::vector<std::string> mPeopleKeywords;
	static std::vector<std::string> mPlacesKeywords;
	static std::vector<std::string> mMysteryKeywords;
	static std::vector<std::string> mBestiaryKeywords;

	static std::vector<Weapon> mInventoryWeapons;

	static int mLevelExpAmounts[];

	static uint8_t mLevelGauranteeStats[];
};