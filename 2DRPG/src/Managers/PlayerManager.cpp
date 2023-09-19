#include "PlayerManager.h"

std::vector<CharacterAttributes> PlayerManager::mCharacterAttributes;
std::vector<SDL_Texture*> PlayerManager::mCharacterTextures;
std::vector<std::string> PlayerManager::mLearnedKeywords;

int PlayerManager::mPartyMoney = 10000;

void PlayerManager::LoadCharacters()
{
    SDL_Surface* surface = nullptr;

    std::string fileName = "./assets/PlayerSaveFile.txt";
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
                else if (type == "Level") file >> newCharacterAttributes.level;
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

            mCharacterAttributes.push_back(newCharacterAttributes);

            SDL_Texture* texture = nullptr;
            std::string surfacePath;
            switch (newCharacterAttributes.characterClass)
            {
                case DANCER:
                {
                    surfacePath = "./assets/Dancer.png";
                    surface = IMG_Load(surfacePath.c_str());
                    if (surface)
                    {
                        texture = SDL_CreateTextureFromSurface(GraphicsManager::Renderer(), surface);
                        mCharacterTextures.push_back(texture);
                    }
                    break;
                }
                case KNIGHT:
                {
                    surfacePath = "./assets/Knight.png";
                    surface = IMG_Load(surfacePath.c_str());
                    if (surface)
                    {
                        texture = SDL_CreateTextureFromSurface(GraphicsManager::Renderer(), surface);
                        mCharacterTextures.push_back(texture);
                    }
                    break;
                }
                case MAGE:
                {
                    surfacePath = "./assets/Mage.png";
                    surface = IMG_Load(surfacePath.c_str());
                    if (surface)
                    {
                        texture = SDL_CreateTextureFromSurface(GraphicsManager::Renderer(), surface);
                        mCharacterTextures.push_back(texture);
                    }
                    break;
                }
                case PALADIN:
                {
                    surfacePath = "./assets/Sigurd.png";
                    surface = IMG_Load(surfacePath.c_str());
                    if (surface)
                    {
                        texture = SDL_CreateTextureFromSurface(GraphicsManager::Renderer(), surface);
                        mCharacterTextures.push_back(texture);
                    }
                    break;
                }
            }
        }
    }

    if (surface)
    {
        SDL_FreeSurface(surface);
    }
}

void PlayerManager::SaveCharacters()
{
}