#include "SceneRefOverworld.h"

#include <iostream>

SceneRefOverworld::SceneRefOverworld()
{
}

SceneRefOverworld::~SceneRefOverworld()
{
    SDL_DestroyTexture(mSpriteSheet);
}

void SceneRefOverworld::Setup(SDL_Renderer* renderer)
{
    std::string fileName = "./assets/WorldSpriteSheet.png";
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    int i = 0;

    std::ifstream file("./assets/WorldSaveFile.txt");
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mapWidth >> mapHeight;

            std::cout << mapWidth << ',' << mapHeight << std::endl;

            Engine::mapWidth = mapWidth;
            Engine::mapHeight = mapHeight;
        }
        else if (type == "SceneEntrance")
        {
            int sceneName;
            int sceneEntranceIndex;
            int sceneEntrancePosX;
            int sceneEntrancePosY;
            file >> sceneName >> sceneEntranceIndex >> sceneEntrancePosX >> sceneEntrancePosY;
        }
        else if (type == "Tile")
        {
            int tileType;
            file >> tileType;

            Tile newTile =
            {
                tileType,
                Vec2((i % mapWidth) * TILE_SIZE, (i / mapWidth) * TILE_SIZE)
            };

            mTiles.push_back(newTile);
            i++;
        }
    }

    mSigurd.Init("./assets/Sigurd_Idle.png", renderer);
}

void SceneRefOverworld::Shutdown()
{
}

void SceneRefOverworld::Input()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
            case SDL_KEYDOWN:
            {
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    Engine::SetIsRunning(false);
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_w)
                {
                    mSigurd.mInput.upPressed = true;
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_s)
                {
                    mSigurd.mInput.downPressed = true;
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_a)
                {
                    mSigurd.mInput.leftPressed = true;
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_d)
                {
                    mSigurd.mInput.rightPressed = true;
                    break;
                }
                break;
            }
            case SDL_KEYUP:
            {
                if (sdlEvent.key.keysym.sym == SDLK_w)
                {
                    mSigurd.mInput.upPressed = false;
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_s)
                {
                    mSigurd.mInput.downPressed = false;
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_a)
                {
                    mSigurd.mInput.leftPressed = false;
                    break;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_d)
                {
                    mSigurd.mInput.rightPressed = false;
                    break;
                }
                break;
            }
        }
    }
}

void SceneRefOverworld::Update(const float dt)
{
    mSigurd.Update(dt);
}

void SceneRefOverworld::Render(SDL_Renderer* renderer)
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

    mSigurd.Render(renderer);
}