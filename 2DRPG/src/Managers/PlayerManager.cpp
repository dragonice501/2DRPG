#include "PlayerManager.h"

#include <cmath>

std::vector<CharacterAttributes> PlayerManager::mCharacterAttributes;
int PlayerManager::mCharacterWeaponIndeces[4] = { -1, -1, -1, -1 };

int PlayerManager::mPartyGold = 2000;

std::vector<std::string> PlayerManager::mPeopleKeywords;
std::vector<std::string> PlayerManager::mPlacesKeywords;
std::vector<std::string> PlayerManager::mMysteryKeywords;
std::vector<std::string> PlayerManager::mBestiaryKeywords;

std::vector<Weapon> PlayerManager::mInventoryWeapons;
std::vector<Armour> PlayerManager::mInventoryArmour;

uint8_t PlayerManager::mLevelGauranteeStats[2] =
{
    170, 85
};

void PlayerManager::LoadCharacters()
{
    if (!GameManager::LoadedGame())
    {
        std::string fileName = "./assets/files/PlayerSaveFile.txt";
        std::ifstream file(fileName);
        std::string type;
        while (file >> type)
        {
            if (type == "Character")
            {
                CharacterAttributes newCharacterAttributes;
                file >> newCharacterAttributes.characterName;

                while (file >> type)
                {
                    if (type == "Class")
                    {
                        int characterClass;
                        file >> characterClass;
                        newCharacterAttributes.characterClass = static_cast<ECharacterClass>(characterClass);
                    }
                    else if (type == "Level")
                    {
                        file >> newCharacterAttributes.level;
                    }
                    else if (type == "Health")
                    {
                        file >> newCharacterAttributes.healthMax;
                        newCharacterAttributes.health = newCharacterAttributes.healthMax;
                    }
                    else if (type == "Magic")
                    {
                        file >> newCharacterAttributes.magicMax;
                        newCharacterAttributes.magic = newCharacterAttributes.magicMax;
                    }
                    else if (type == "Strength") file >> newCharacterAttributes.strength;
                    else if (type == "Defense") file >> newCharacterAttributes.defense;
                    else if (type == "Intelligence") file >> newCharacterAttributes.intelligence;
                    else if (type == "Speed") file >> newCharacterAttributes.speed;
                    else if (type == "Skill") file >> newCharacterAttributes.skill;
                    else if (type == "Luck") file >> newCharacterAttributes.luck;
                    else if (type == "Exp")
                    {
                        file >> newCharacterAttributes.exp;
                        newCharacterAttributes.expNextLevel = CalcLevelUpExp(newCharacterAttributes.level);
                        break;
                    }
                }

                mCharacterAttributes.push_back(newCharacterAttributes);
            }
        }
    }

    for (int i = 0; i < mCharacterAttributes.size(); i++)
    {
        std::string textureName = GetClassName(mCharacterAttributes[i].characterClass);

        AssetManager::CreateCharacterTexture(i, textureName);
    }
}

void PlayerManager::SaveCharacters()
{
}

int PlayerManager::CalcLevelUpExp(int level)
{
    return (5 * pow(level, 3)) / 4 + 24;
}

bool PlayerManager::CheckLevelUp(int& outIndex)
{
    if (outIndex >= mCharacterAttributes.size()) outIndex = 0;

    for (int i = outIndex; i < mCharacterAttributes.size(); i++)
    {
        if (mCharacterAttributes[i].exp >= mCharacterAttributes[i].expNextLevel)
        {
            outIndex = i;
            return true;
        }
    }

    outIndex = -1;
    return false;
}

CharacterAttributes PlayerManager::LevelUp(int characterIndex)
{
    CharacterAttributes levelUpAttributes;
    CharacterAttributes& attributes = mCharacterAttributes[characterIndex];
    attributes.level++;
    attributes.expNextLevel = CalcLevelUpExp(attributes.level);

    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 7))
    {
        attributes.healthMax++;
        attributes.health = attributes.healthMax;
        levelUpAttributes.health++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 6))
    {
        attributes.magicMax++;
        attributes.magic = attributes.magicMax;
        levelUpAttributes.magic++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 5))
    {
        attributes.strength++;
        levelUpAttributes.strength++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 4))
    {
        attributes.defense++;
        levelUpAttributes.defense++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 3))
    {
        attributes.intelligence++;
        levelUpAttributes.intelligence++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 2))
    {
        attributes.speed++;
        levelUpAttributes.speed++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 1))
    {
        attributes.skill++;
        levelUpAttributes.skill++;
    }
    if (mLevelGauranteeStats[attributes.level - 2] & (1 << 0))
    {
        attributes.luck++;
        levelUpAttributes.luck++;
    }

    return levelUpAttributes;
}

void PlayerManager::SwapCharacters(int first, int second)
{
    CharacterAttributes tempChar = mCharacterAttributes[first];
    mCharacterAttributes[first] = mCharacterAttributes[second];
    mCharacterAttributes[second] = tempChar;

    AssetManager::SwapCharacterTexture(first, second);
}

void PlayerManager::SwapCharacterInventories(int first, int second)
{
    int tempWeapon = mCharacterWeaponIndeces[first];
    mCharacterWeaponIndeces[first] = mCharacterWeaponIndeces[second];
    mCharacterWeaponIndeces[second] = tempWeapon;
}

bool PlayerManager::CanEquipWeapon(int weaponIndex)
{
    for (int i = 0; i < 4; i++)
    {
        if (mCharacterWeaponIndeces[i] == weaponIndex) return false;
    }

    return true;
}