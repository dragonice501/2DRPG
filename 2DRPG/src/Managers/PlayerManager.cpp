#include "PlayerManager.h"

std::vector<CharacterAttributes> PlayerManager::mCharacterAttributes;
std::vector<SDL_Texture*> PlayerManager::mCharacterTextures;

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
            std::string characterName;
            int health, healthMax, magic, magicMax, strength, defense, intelligence, speed, skill, luck, characterClass;

            file >>
                characterName >> health >> healthMax >> magic >> magicMax >>
                strength >> defense >> intelligence >> speed >> skill >> luck >>
                characterClass;

            CharacterAttributes newCharacterAttributes =
            {
                characterName, static_cast<ECharacterClass>(characterClass),
                health, healthMax, magic, magicMax,
                strength, defense, intelligence, speed, skill, luck
            };

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