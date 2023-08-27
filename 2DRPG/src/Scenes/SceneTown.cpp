#include "SceneTown.h"

SceneTown::~SceneTown()
{
	SDL_DestroyTexture(mSpriteSheet);
}

void SceneTown::Setup(static SDL_Renderer* renderer)
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
        spawnPosition = Vec2(16.0f, 17.0f) * TILE_SIZE;
    }

    mSigurd.Init("Sigurd", "SigurdAnimations", spawnPosition, renderer);
}

void SceneTown::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTown::Input()
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
                    mCharacterState = CS_INTERACTING;
                    mInteractedActor = &actor;
                }
            }
        }
        else
        {
            mCharacterState = CS_MOVING;
            mInteractedActor = nullptr;
        }
    }
}

void SceneTown::Update(const float dt)
{
    SceneExploration::Update(dt);

    for (Actor& actor : mActors)
    {
        actor.Update(dt);
    }

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
                    SceneManager::SetSceneToLoad(OVERWORLD, entrance.sceneEntranceIndex);
                }
            }
        }
    }
}

void SceneTown::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
{
    camera.x = mSigurd.GetPosition().x * TILE_SPRITE_SCALE - (GraphicsManager::WindowWidth() / 2);
    camera.y = mSigurd.GetPosition().y * TILE_SPRITE_SCALE - (GraphicsManager::WindowHeight() / 2);

    camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
    camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);

    SceneExploration::Render(renderer, camera);

    for (Actor& actor : mActors)
    {
        actor.Render(renderer);
    }

    mSigurd.Render(renderer);

    if (mCharacterState == CS_INTERACTING)
    {
        //GraphicsManager::DrawFillRect(GraphicsManager::WindowWidth() / 2 - 150, GraphicsManager::WindowHeight() / 4, 300, 50, 0xFFFFFFFF);
        GraphicsManager::DrawDialogueBox();

        GraphicsManager::DrawString(
            GraphicsManager::WindowWidth() / 2 - 130,
            GraphicsManager::WindowHeight() / 4 + 20,
            mInteractedActor->GetDialogue("Greeting").c_str(),
            0xFFFFFFFF,
            true);
    }
}