#include "AssetManager.h"

SDL_Texture* AssetManager::mTileMapTexture = nullptr;
SDL_Texture* AssetManager::mMenuIconsTexture = nullptr;
SDL_Texture* AssetManager::mBattleBackgroundTexture = nullptr;
SDL_Texture* AssetManager::mEnemiesTexture = nullptr;
std::vector<SDL_Texture*> AssetManager::mCharacterTextures;

std::string AssetManager::mMenuIconsFilePath;
std::string AssetManager::mBattleBackgroundImageFilePath;

std::map<std::string, Sprite> AssetManager::mBattleIconsMap;
std::map<std::string, SDL_Texture*> AssetManager::mAssetMap;

void AssetManager::CreateTileMapTexture(const std::string& textureName)
{
	SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/images/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mTileMapTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateMenuIconsTexture()
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/images/MenuIcons.png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mMenuIconsTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateBattleBackgroundTexture(const std::string& textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/images/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mBattleBackgroundTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateEnemiesTexture(const std::string& textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/images/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mEnemiesTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void AssetManager::CreateCharacterTexture(const std::string& textureName)
{
    if (mAssetMap.find(textureName) != mAssetMap.end()) return;

    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/images/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        //mCharacterTextures.push_back(SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface));
        mAssetMap.emplace(textureName, SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface));
    }

    SDL_FreeSurface(surface);
}

void AssetManager::BuildMenuIconMap()
{
    std::string type;
    std::ifstream battleIconsFile("./assets/files/BattleIcons.txt");
    while (battleIconsFile >> type)
    {
        if (type == "Cursor")
        {
            Sprite newSprite;

            battleIconsFile >> newSprite.srcRect.x >> newSprite.srcRect.y >> newSprite.srcRect.w >> newSprite.srcRect.h;
            mBattleIconsMap.emplace("Cursor", newSprite);
        }
    }
}

void AssetManager::SwapCharacterTexture(int first, int second)
{
    SDL_Texture* tempTex = mCharacterTextures[first];
    mCharacterTextures[first] = mCharacterTextures[second];
    mCharacterTextures[second] = tempTex;
}