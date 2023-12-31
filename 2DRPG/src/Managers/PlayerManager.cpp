#include "PlayerManager.h"

#include <cmath>

std::vector<CharacterAttributes> PlayerManager::mCharacterAttributes;
int PlayerManager::mCharacterWeaponIndeces[4] = { -1, -1, -1, -1 };
int PlayerManager::mCharacterShieldIndeces[4] = { -1, -1, -1, -1 };
int PlayerManager::mCharacterArmourHeadIndeces[4] = { -1, -1, -1, -1 };
int PlayerManager::mCharacterArmourBodyIndeces[4] = { -1, -1, -1, -1 };

int PlayerManager::mPartyGold = 2000;

std::vector<std::string> PlayerManager::mPeopleKeywords;
std::vector<std::string> PlayerManager::mPlacesKeywords;
std::vector<std::string> PlayerManager::mMysteryKeywords;
std::vector<std::string> PlayerManager::mBestiaryKeywords;

std::vector<Weapon> PlayerManager::mInventoryWeapons;
std::vector<Shield> PlayerManager::mInventoryShields;
std::vector<Armour> PlayerManager::mInventoryArmourHead;
std::vector<Armour> PlayerManager::mInventoryArmourBody;

uint8_t PlayerManager::mLevelGauranteeStatsDancer[10] =
{
    128,128,128,128,128,128,128,128,128,128
};
uint8_t PlayerManager::mLevelGauranteeStatsKnight[10] =
{
    128,128,128,128,128,128,128,128,128,128
};
uint8_t PlayerManager::mLevelGauranteeStatsMage[10] =
{
    128,128,128,128,128,128,128,128,128,128
};
uint8_t PlayerManager::mLevelGauranteeStatsPaladin[10] =
{
    128,128,128,128,128,128,128,128,128,128
};

void PlayerManager::LoadCharacters()
{
    int index = 0;
    if (!GameManager::LoadedGame())
    {
        std::string basePath = SDL_GetBasePath();
        std::string filePath = "assets\\files\\PlayerSaveFile.txt";
        std::ifstream file(basePath + filePath);
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

                mCharacterAttributes[index] = newCharacterAttributes;
                index++;
            }
        }
    }

    for (int i = 0; i < mCharacterAttributes.size(); i++)
    {
        std::string textureName = GetClassName(mCharacterAttributes[i].characterClass);

        AssetManager::CreateCharacterTexture(textureName);
    }
}

void PlayerManager::SaveCharacters()
{
}

void PlayerManager::SetupCharacters()
{
    for (int i = 0; i < 4; i++)
    {
        mCharacterAttributes.push_back(CharacterAttributes());
    }
}

void PlayerManager::LoadNewGameDefaultCharacters()
{
    std::string className;
    for (int i = 0; i < 4; i++)
    {
        mCharacterAttributes[i].characterClass = static_cast<ECharacterClass>(GameManager::GetNewGameClass(i));

        switch (mCharacterAttributes[i].characterClass)
        {
            case DANCER:
            {
                className = "Dancer";
                break;
            }
            case KNIGHT:
            {
                className = "Knight";
                break;
            }
            case MAGE:
            {
                className = "Mage";
                break;
            }
            case PALADIN:
            {
                className = "Paladin";
                break;
            }
        }

        LoadClassStartingAttributes(i, className);

        mCharacterAttributes[i].characterClass = static_cast<ECharacterClass>(GameManager::GetNewGameClass(i));
        mCharacterAttributes[i].characterName = GameManager::GetNewGameName(i);
    }
}

void PlayerManager::LoadClassStartingAttributes(int partyIndex, const std::string& className)
{
    std::string basePath = SDL_GetBasePath();
    std::string fileName = "assets\\files\\ClassStartingStats.txt";
    std::ifstream file(basePath + fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "Class")
        {
            file >> type;
            if (type == className)
            {
                CharacterAttributes newCharacterAttributes;

                while (file >> type)
                {
                    if (type == "Level")
                    {
                        file >> newCharacterAttributes.level;
                        newCharacterAttributes.expNextLevel = CalcLevelUpExp(newCharacterAttributes.level);
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
                    else if (type == "Luck")
                    {
                        file >> newCharacterAttributes.luck;
                        break;
                    }
                }

                mCharacterAttributes[partyIndex] = newCharacterAttributes;
                break;
            }
            else
            {
                for (int i = 0; i < 10; i++)
                    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

int PlayerManager::CalcLevelUpExp(int level)
{
    if (level == 0) return 0;

    return (5 * pow(level, 3)) / 4 + 6;
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

CharacterAttributes PlayerManager::LevelUp(int characterIndex, bool* outStats)
{
    CharacterAttributes levelUpAttributes;
    CharacterAttributes& attributes = mCharacterAttributes[characterIndex];
    attributes.level++;
    attributes.expNextLevel = CalcLevelUpExp(attributes.level);

    uint8_t* mLevelUpStats = nullptr;
    switch (attributes.characterClass)
    {
        case DANCER:
        {
            mLevelUpStats = mLevelGauranteeStatsDancer;
            break;
        }
        case KNIGHT:
        {
            mLevelUpStats = mLevelGauranteeStatsKnight;
            break;
        }
        case MAGE:
        {
            mLevelUpStats = mLevelGauranteeStatsMage;
            break;
        }
        case PALADIN:
        {
            mLevelUpStats = mLevelGauranteeStatsPaladin;
            break;
        }
    }

    if (mLevelUpStats)
    {
        if (mLevelUpStats[attributes.level - 2] & (1 << 7))
        {
            attributes.healthMax++;
            attributes.health = attributes.healthMax;
            levelUpAttributes.health++;

            outStats[0] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 6))
        {
            attributes.magicMax++;
            attributes.magic = attributes.magicMax;
            levelUpAttributes.magic++;

            outStats[1] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 5))
        {
            attributes.strength++;
            levelUpAttributes.strength++;

            outStats[2] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 4))
        {
            attributes.defense++;
            levelUpAttributes.defense++;

            outStats[3] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 3))
        {
            attributes.intelligence++;
            levelUpAttributes.intelligence++;

            outStats[4] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 2))
        {
            attributes.speed++;
            levelUpAttributes.speed++;

            outStats[5] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 1))
        {
            attributes.skill++;
            levelUpAttributes.skill++;

            outStats[6] = true;
        }
        if (mLevelUpStats[attributes.level - 2] & (1 << 0))
        {
            attributes.luck++;
            levelUpAttributes.luck++;

            outStats[7] = true;
        }
    }
    
    return levelUpAttributes;
}

void PlayerManager::RemoveAllEquipment(const int characterIndex)
{
    mCharacterWeaponIndeces[characterIndex] = -1;
    mCharacterShieldIndeces[characterIndex] = -1;
    mCharacterArmourHeadIndeces[characterIndex] = -1;
    mCharacterArmourBodyIndeces[characterIndex] = -1;
}

int PlayerManager::GetPlayerWeaponDamage(const int index)
{
    if (mCharacterWeaponIndeces[index] != -1) return mInventoryWeapons[mCharacterWeaponIndeces[index]].mAttack;
    else return 0;
}

void PlayerManager::SwapCharacters(int first, int second)
{
    CharacterAttributes tempChar = mCharacterAttributes[first];
    mCharacterAttributes[first] = mCharacterAttributes[second];
    mCharacterAttributes[second] = tempChar;
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

bool PlayerManager::CanEquipShield(int shieldIndex)
{
    for (int i = 0; i < 4; i++)
    {
        if (mCharacterShieldIndeces[i] == shieldIndex) return false;
    }

    return true;
}

bool PlayerManager::CanEquipArmourHead(int armourIndex)
{
    for (int i = 0; i < 4; i++)
    {
        if (mCharacterArmourHeadIndeces[i] == armourIndex) return false;
    }

    return true;
}

bool PlayerManager::CanEquipArmourBody(int armourIndex)
{
    for (int i = 0; i < 4; i++)
    {
        if (mCharacterArmourBodyIndeces[i] == armourIndex) return false;
    }

    return true;
}