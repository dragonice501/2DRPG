#include "PlayerManager.h"

std::vector<CharacterAttributes> PlayerManager::mCharacterAttributes;
std::vector<ECharacterClass> PlayerManager::mCharacterClasses;
std::vector<SDL_Texture*> PlayerManager::mCharacterTextures;

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
            int health, healthMax, magic, magicMax, strength, defense, intelligence, speed, skill, luck, characterClass;

            file >>
                characterName >> health >> healthMax >> magic >> magicMax >>
                strength >> defense >> intelligence >> speed >> skill >> luck >>
                characterClass;

            CharacterAttributes newCharacterAttributes =
            {
                characterName, health, healthMax, magic, magicMax,
                strength, defense, intelligence, speed, skill, luck
            };

            mCharacterAttributes.push_back(newCharacterAttributes);
            mCharacterClasses.push_back(static_cast<ECharacterClass>(characterClass));

            SDL_Surface* surface = nullptr;
            SDL_Texture* texture = nullptr;
            std::string surfacePath;
            switch (static_cast<ECharacterClass>(characterClass))
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
                }

            }

            if (surface)
            {
                SDL_FreeSurface(surface);
            }
        }
    }
}

void PlayerManager::SaveCharacters()
{
}