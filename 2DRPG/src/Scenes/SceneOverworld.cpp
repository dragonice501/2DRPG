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

    if (SceneManager::GetSceneEntranceIndex() == -1)
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
        if (mCharacterState != CS_INTERACTING)
        {
            Vec2 position = mSigurd.GetPosition() + mSigurd.mRigidbody.lastVelocity;
            for (Actor& actor : mActors)
            {
                if (position == actor.GetPosition())
                {
                    std::cout << "interaction made at " << position.x << ',' << position.y << std::endl;
                }
            }
        }
        else
        {
            mCharacterState = CS_MOVING;
        }
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