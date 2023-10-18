#include "AssetManager.h"

SDL_Texture* AssetManager::mTileMapTexture = nullptr;
SDL_Texture* AssetManager::mMenuIconsTexture = nullptr;
SDL_Texture* AssetManager::mBattleBackgroundTexture = nullptr;
SDL_Texture* AssetManager::mEnemiesTexture = nullptr;
std::vector<SDL_Texture*> AssetManager::mCharacterTextures;

std::string AssetManager::mMenuIconsFilePath;
std::string AssetManager::mBattleBackgroundImageFilePath;

void AssetManager::CreateTileMapTexture(const std::string textureName)
{
	SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mTileMapTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateMenuIconsTexture(const std::string textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mMenuIconsTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateBattleBackgroundTexture(const std::string textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mBattleBackgroundTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateEnemiesTexture(const std::string textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mEnemiesTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateCharacterTexture(int index, const std::string textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mCharacterTextures.push_back(SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface));
    }

    SDL_FreeSurface(surface);
}

void AssetManager::SwapCharacterTexture(int first, int second)
{
    SDL_Texture* tempTex = mCharacterTextures[first];
    mCharacterTextures[first] = mCharacterTextures[second];
    mCharacterTextures[second] = tempTex;
}