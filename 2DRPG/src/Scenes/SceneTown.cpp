#include "SceneTown.h"

SceneTown::~SceneTown()
{
	SDL_DestroyTexture(mTileMap);
}

void SceneTown::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    if (GameManager::GetSceneEntranceIndex() == -1)
    {
        mSpawnPositions.clear();
        mSpawnPositions.push_back(Vec2(16.0f, 17.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(17.0f, 17.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(17.0f, 18.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(16.0f, 18.0f) * TILE_SIZE);
    }

    SceneExploration::SetupCharacters();
}

void SceneTown::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTown::Input()
{
    SceneExploration::Input();

   /* if (mCharacterState == CS_INTERACT_MENU)
    {
        if (InputManager::UpPressed())
        {
            mInteractMenuIndex--;
            if (mInteractMenuIndex < 0) mInteractMenuIndex = 2;
        }
        if (InputManager::DownPressed())
        {
            mInteractMenuIndex++;
            if (mInteractMenuIndex > 2) mInteractMenuIndex = 0;
        }
    }

    if (InputManager::EPressed())
    {
        if (mCharacterState == CS_MOVING)
        {
            Vec2 position = mCharacters[0].GetPosition() + mCharacters[0].mRigidbody.lastVelocity;
            for (Actor& actor : mActors)
            {
                if (position == actor.GetPosition())
                {
                    mCharacterState = CS_INTERACT_MENU;
                    mInteractedActor = &actor;
                }
            }
        }
        else if(mCharacterState == CS_INTERACT_MENU)
        {
            if (mInteractMenuIndex == 0)
            {
                mCharacterState = CS_TALKING;
            }
            else if (mInteractMenuIndex == 1)
            {

            }
            else if (mInteractMenuIndex == 2)
            {
                mCharacterState = CS_MOVING;
                mInteractedActor = nullptr;
                mInteractMenuIndex = 0;
            }
        }
        else if (mCharacterState == CS_TALKING)
        {
            if (mInteractedActor && mInteractedActor->CycleThroughDialogue()) {}
            else
            {
                mCharacterState = CS_INTERACT_MENU;
            }
        }
    }*/
}

void SceneTown::Update(const float dt)
{
    SceneExploration::Update(dt);
}

void SceneTown::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
{
    SceneExploration::Render(renderer, camera);

    for (Actor& actor : mActors)
    {
        actor.Render(renderer);
    }

    for (int i = mCharacters.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            camera.x = mCharacters[i].GetPosition().x * TILE_SPRITE_SCALE - (GraphicsManager::WindowWidth() / 2);
            camera.y = mCharacters[i].GetPosition().y * TILE_SPRITE_SCALE - (GraphicsManager::WindowHeight() / 2);

            camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
            camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
        }

        mCharacters[i].Render(renderer);
    }

    if (mExplorationState == ES_MENUING)
    {
        DrawPartyMenu(renderer);
    }
    else if (mCharacterState == CS_INTERACT_MENU)
    {
        SDL_Rect rect = GraphicsManager::DrawUIBox(GraphicsManager::WindowWidth() / 2 - 150, GraphicsManager::WindowHeight() / 2 - 50, INTERACT_MENU_WIDTH, INTERACT_MENU_HEIGHT);
        GraphicsManager::DrawUISelector(rect.x, rect.y + 30 * mInteractMenuIndex, rect.w, 30);

        GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, "Talk", 0xFFFFFFFF);
        GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 30, "Ask", 0xFFFFFFFF);
        GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 60, "Leave", 0xFFFFFFFF);
    }
    else if (mCharacterState == CS_TALKING)
    {
        SDL_Rect rect = GraphicsManager::DrawDialogueBox();
        GraphicsManager::DrawDialogue(rect, mInteractedActor->GetDialogue());
    }
}