#include "SceneTown.h"

SceneTown::SceneTown()
{
}

SceneTown::~SceneTown()
{
	SDL_DestroyTexture(mSpriteSheet);
}

void SceneTown::Setup(SDL_Renderer* renderer)
{
    std::string fileName = "./assets/TownSpriteSheet.png";
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    int i = 0;
    Vec2 spawnPosition;

    std::ifstream file("./assets/TownSaveFile.txt");
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mapWidth >> mapHeight;

            Engine::mapWidth = mapWidth;
            Engine::mapHeight = mapHeight;
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

            if (sceneEntranceIndex == SceneManager::Instance().GetSceneEntranceIndex())
            {
                spawnPosition =
                {
                    static_cast<float>(sceneEntrancePosX * TILE_SIZE + sceneEntranceOffsetX * TILE_SIZE),
                    static_cast<float>(sceneEntrancePosY * TILE_SIZE + sceneEntranceOffsetY * TILE_SIZE)
                };
            }
        }
        else if (type == "Tile")
        {
            int tileType;
            file >> tileType;

            Tile newTile =
            {
                static_cast<size_t>(tileType),
                Vec2((i % mapWidth) * TILE_SIZE, (i / mapWidth) * TILE_SIZE)
            };

            mTiles.push_back(newTile);
            i++;
        }
    }

    mSigurd.Init("./assets/Sigurd.png", "SigurdAnimations", spawnPosition, renderer);
}

void SceneTown::Shutdown()
{
    mTiles.clear();
}

void SceneTown::Input()
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

void SceneTown::Update(const float dt)
{
    mSigurd.UpdateMovement(mapWidth, mapHeight, mTiles, dt);
    mSigurd.Update(dt);

    if (mSigurd.mMovement.stepTaken)
    {
        for (const SceneEntrance& entrance : mSceneEntrances)
        {
            if (mSigurd.position == entrance.position)
            {
                SceneManager::Instance().SetSceneToLoad(OVERWORLD, entrance.sceneEntranceIndex);
            }
        }
    }
}

void SceneTown::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
    camera.x = mSigurd.position.x * TILE_SPRITE_SCALE - (Engine::mWindowWidth / 2);
    camera.y = mSigurd.position.y * TILE_SPRITE_SCALE - (Engine::mWindowHeight / 2);

    camera.x = Clampf(camera.x, 0, mapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
    camera.y = Clampf(camera.y, 0, mapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);

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