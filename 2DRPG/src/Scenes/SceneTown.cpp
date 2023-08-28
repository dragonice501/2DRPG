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
    if (mCharacterState == CS_INTERACT_MENU)
    {
        if (InputManager::UpPressed())
        {
            mInteractMenuIndex--;
            if (mInteractMenuIndex < 0) mInteractMenuIndex = 1;
        }
        if (InputManager::DownPressed())
        {
            mInteractMenuIndex++;
            if (mInteractMenuIndex > 1) mInteractMenuIndex = 0;
        }
    }

    if (InputManager::EPressed())
    {
        if (mCharacterState != CS_INTERACT_MENU)
        {
            Vec2 position = mSigurd.GetPosition() + mSigurd.mRigidbody.lastVelocity;
            for (Actor& actor : mActors)
            {
                if (position == actor.GetPosition())
                {
                    mCharacterState = CS_INTERACT_MENU;
                    mInteractedActor = &actor;
                }
            }
        }
        else
        {
            /*if (mInteractedActor && mInteractedActor->CycleThroughDialogue()) {}
            else
            {
                mCharacterState = CS_MOVING;
                mInteractedActor = nullptr;
            }*/

            mCharacterState = CS_MOVING;
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
        GraphicsManager::DrawDialogueBox();

        GraphicsManager::DrawString(
            GraphicsManager::WindowWidth() / 2 - DIALOGUE_BOX_WIDTH / 2 + TEXT_PADDING,
            GraphicsManager::WindowHeight() * 0.75f + DIALOGUE_BOX_HEIGHT / 2 - DIALOGUE_BOX_HEIGHT / 2 + TEXT_PADDING,
            mInteractedActor->GetDialogue().c_str(),
            0xFFFFFFFF,
            true);
    }
    else if (mCharacterState == CS_INTERACT_MENU)
    {
        SDL_Rect rect = GraphicsManager::DrawUIBox(GraphicsManager::WindowWidth() / 2 - 150, GraphicsManager::WindowHeight() / 2 - 50, INTERACT_MENU_WIDTH, INTERACT_MENU_HEIGHT);
        GraphicsManager::DrawUISelector(rect.x, rect.y + 30 * mInteractMenuIndex, rect.w, 30);

        GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, "Talk", 0xFFFFFFFF);
        GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 30, "Ask", 0xFFFFFFFF);
    }
}