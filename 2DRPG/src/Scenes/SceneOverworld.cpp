#include "SceneOverworld.h"

#include <iostream>

SceneOverworld::~SceneOverworld()
{
    
}

void SceneOverworld::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    for (const SceneEntrance& entrance : mSceneEntrances)
    {
        if (entrance.sceneEntranceIndex == SceneManager::GetSceneEntranceIndex())
        {
            spawnPosition = entrance.position + entrance.spawnOffset;
            mSigurd.mRigidbody.lastVelocity = entrance.spawnOffset;
        }
    }

    if (SceneManager::ReturnToOverworld())
    {
        spawnPosition = SceneManager::GetPreviousOverworldPosition();
        mSigurd.mRigidbody.lastVelocity = SceneManager::GetPreviousDirection();
    }
    else if (SceneManager::GetSceneEntranceIndex() == -1)
    {
        spawnPosition = Vec2(39.0f, 32.0f) * TILE_SIZE;
    }

    mSigurd.Init("Sigurd", "SigurdAnimations", spawnPosition, renderer);
}

void SceneOverworld::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneOverworld::Input()
{
    if (InputManager::EPressed())
    {
        
    }
}

void SceneOverworld::Update(const float dt)
{
    SceneExploration::Update(dt);

    if (mCharacterState == CS_MOVING)
    {
        mSigurd.UpdateMovement(mMapWidth, mMapHeight, mTiles, mActors, dt);
        mSigurd.Update(dt);

        if (mSigurd.mMovement.stepTaken)
        {
            for (const SceneEntrance& entrance : mSceneEntrances)
            {
                if (mSigurd.GetPosition() == entrance.position)
                {
                    SceneManager::SetSceneToLoad(TOWN, entrance.sceneEntranceIndex);
                }
            }

            if (SceneManager::GetIsOverworld())
            {
                mStepsUntilEncounter--;
                if (mStepsUntilEncounter <= 0)
                {
                    int index = mSigurd.GetPosition().x / TILE_SIZE + (mSigurd.GetPosition().y * mMapWidth) / TILE_SIZE;
                    ETerrainType currentTerrain = mTiles[index].terrainType;

                    SceneManager::SetPreviousOverworldPosition(mSigurd.GetPosition());
                    SceneManager::SetPreviousDirection(mSigurd.mRigidbody.lastVelocity);
                    SceneManager::SetSceneToLoad(BATTLE, -1, currentTerrain);
                }
            }
        }
    }
}

void SceneOverworld::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
{
    camera.x = mSigurd.GetPosition().x * TILE_SPRITE_SCALE - (GraphicsManager::WindowWidth() / 2);
    camera.y = mSigurd.GetPosition().y * TILE_SPRITE_SCALE - (GraphicsManager::WindowHeight() / 2);

    camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
    camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
    
    SceneExploration::Render(renderer, camera);

    mSigurd.Render(renderer);
}