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
        if (entrance.sceneEntranceIndex == SceneManager::GetSceneEntranceIndex())
        {
            spawnPosition = entrance.position + entrance.spawnOffset;
        }
    }

    if (SceneManager::GetSceneEntranceIndex() == -1)
    {
        spawnPosition = Vec2(39.0f, 32.0f) * TILE_SIZE;
    }

    mSigurd.Init("Sigurd", "SigurdAnimations", spawnPosition, renderer);
    if (GameManager::GetExitVelocity() != Vec2(0.0f))
    {
        mSigurd.mRigidbody.lastVelocity = GameManager::GetExitVelocity();
    }
}

void SceneOverworld::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneOverworld::Input()
{
    
}

void SceneOverworld::Update(const float dt)
{
    SceneExploration::Update(dt);

    mSigurd.UpdateMovement(mMapWidth, mMapHeight, mTiles, mActors, dt);
    mSigurd.Update(dt);

    if (mSigurd.mMovement.stepTaken)
    {
        for (const SceneEntrance& entrance : mSceneEntrances)
        {
            if (mSigurd.GetPosition() == entrance.position)
            {
                GameManager::SetExitVelocity(mSigurd.mRigidbody.lastVelocity);
                SceneManager::SetSceneToLoad(TOWN, entrance.sceneEntranceIndex);
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