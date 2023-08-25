#include "SceneExploration.h"

SceneExploration::SceneExploration()
{
    
}

SceneExploration::~SceneExploration()
{
}

void SceneExploration::Setup(SDL_Renderer* renderer)
{
    std::string fileName = "./assets/" + mFileName + "SpriteSheet.png";
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    int i = 0;
    Vec2 spawnPosition;

    fileName = "./assets/" + mFileName + "SaveFile.txt";
    std::ifstream file(fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mMapWidth >> mMapHeight;

            Engine::mapWidth = mMapWidth;
            Engine::mapHeight = mMapHeight;
        }
        else if (type == "SceneEntrance")
        {
            int sceneName;
            int sceneEntranceIndex;
            int sceneEntrancePosX;
            int sceneEntrancePosY;
            int sceneEntranceOffsetX;
            int sceneEntranceOffsetY;
            file >> sceneName >> sceneEntranceIndex >> sceneEntrancePosX >> sceneEntrancePosY >> sceneEntranceOffsetX >> sceneEntranceOffsetY;

            SceneEntrance newEntrance =
            {
                Vec2(sceneEntrancePosX * TILE_SIZE, sceneEntrancePosY * TILE_SIZE),
                Vec2(sceneEntranceOffsetX * TILE_SIZE, sceneEntranceOffsetY * TILE_SIZE),
                sceneName,
                sceneEntranceIndex
            };

            mSceneEntrances.push_back(newEntrance);
        }
        else if (type == "Tile")
        {
            int tileType;
            file >> tileType;

            Tile newTile =
            {
                static_cast<size_t>(tileType),
                Vec2((i % mMapWidth) * TILE_SIZE, (i / mMapWidth) * TILE_SIZE)
            };

            mTiles.push_back(newTile);
            i++;
        }
    }
}

void SceneExploration::Shutdown()
{
    mTiles.clear();
    mActors.clear();

    SDL_DestroyTexture(mSpriteSheet);
}

void SceneExploration::Input(Character& character)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
        {
            Engine::SetIsRunning(false);
            break;
        }
        switch (sdlEvent.type)
        {
        case SDL_KEYDOWN:
        {
            if (sdlEvent.key.keysym.sym == SDLK_w)
            {
                character.mInput.upPressed = true;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_s)
            {
                character.mInput.downPressed = true;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_a)
            {
                character.mInput.leftPressed = true;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_d)
            {
                character.mInput.rightPressed = true;
                break;
            }
            break;
        }
        case SDL_KEYUP:
        {
            if (sdlEvent.key.keysym.sym == SDLK_w)
            {
                character.mInput.upPressed = false;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_s)
            {
                character.mInput.downPressed = false;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_a)
            {
                character.mInput.leftPressed = false;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_d)
            {
                character.mInput.rightPressed = false;
                break;
            }
            break;
        }
        }
    }
}

void SceneExploration::Update(const float dt)
{
}

void SceneExploration::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
    for (int i = 0; i < mTiles.size(); i++)
    {
        SDL_Rect srcRect =
        {
            mTiles[i].spriteIndex % SPRITE_SHEET_SIZE * TILE_SIZE,
            mTiles[i].spriteIndex / SPRITE_SHEET_SIZE * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
        };

        SDL_Rect destRect =
        {
            mTiles[i].position.x * TILE_SPRITE_SCALE - Engine::Camera().x,
            mTiles[i].position.y * TILE_SPRITE_SCALE - Engine::Camera().y,
            TILE_SIZE * TILE_SPRITE_SCALE,
            TILE_SIZE * TILE_SPRITE_SCALE
        };

        SDL_RenderCopy(renderer, mSpriteSheet, &srcRect, &destRect);
    }
}