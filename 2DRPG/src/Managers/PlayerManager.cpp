#include "PlayerManager.h"

std::vector<CharacterAttributes> PlayerManager::mCharacterAttributes;

void PlayerManager::LoadCharacters()
{
    std::string fileName = "./assets/PlayerSaveFile.txt";
    std::ifstream file(fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "Character")
        {
            std::string characterName;
            int health, healthMax, magic, magicMax, strength, defense, intelligence, speed, skill, luck;

            file >>
                characterName >> health >> healthMax >> magic >> magicMax >>
                strength >> defense >> intelligence >> speed >> skill >> luck;

            CharacterAttributes newCharacterAttributes =
            {
                characterName, health, healthMax, magic, magicMax,
                strength, defense, intelligence, speed, skill, luck
            };

            mCharacterAttributes.push_back(newCharacterAttributes);
        }
    }
}

void PlayerManager::SaveCharacters()
{
}