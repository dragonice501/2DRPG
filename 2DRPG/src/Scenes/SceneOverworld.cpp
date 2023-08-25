#include "SceneOverworld.h"

#include <iostream>

SceneOverworld::~SceneOverworld()
{
    
}

void SceneOverworld::Setup(SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    for (const SceneEntrance& entrance : mSceneEntrances)
    {
        if (entrance.sceneEntranceIndex == SceneManager::Instance().GetSceneEntranceIndex())
        {
            spawnPosition = entrance.position + entrance.spawnOffset;
        }
    }

    mSigurd.Init("Sigurd", "SigurdAnimations", spawnPosition, renderer);
}

void SceneOverworld::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneOverworld::Input()
{
    SceneExploration::Input(mSigurd);
}

void SceneOverworld::Update(const float dt)
{
    SceneExploration::Update(dt);

    mSigurd.UpdateMovement(mMapWidth, mMapHeight, mTiles, dt);
    mSigurd.Update(dt);

    if (mSigurd.mMovement.stepTaken)
    {
        for (const SceneEntrance& entrance : mSceneEntrances)
        {
            if (mSigurd.GetPosition() == entrance.position)
            {
                SceneManager::Instance().SetSceneToLoad(TOWN, entrance.sceneEntranceIndex);
            }
        }
    }
}

void SceneOverworld::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
    camera.x = mSigurd.GetPosition().x * TILE_SPRITE_SCALE - (Engine::mWindowWidth / 2);
    camera.y = mSigurd.GetPosition().y * TILE_SPRITE_SCALE - (Engine::mWindowHeight / 2);

    camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
    camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
    
    SceneExploration::Render(renderer, camera);

    mSigurd.Render(renderer);
}