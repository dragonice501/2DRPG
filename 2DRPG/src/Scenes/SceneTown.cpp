#include "SceneTown.h"

SceneTown::~SceneTown()
{
	SDL_DestroyTexture(mTileMap);
}

void SceneTown::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    if (SceneManager::ReturnToOverworld())
    {
        for (int i = 0; i < PlayerManager::GetCharacterTextures().size(); i++)
        {
            mSpawnPositions.push_back(SceneManager::GetPreviousOverworldPosition(i));
        }
    }
    else if (SceneManager::GetSceneEntranceIndex() == -1)
    {
        mSpawnPosition = Vec2(39.0f, 32.0f) * TILE_SIZE;
        mSpawnPositions.push_back(Vec2(39.0f, 32.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(40.0f, 32.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(40.0f, 33.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(39.0f, 33.0f) * TILE_SIZE);
    }
    else
    {
        for (const SceneEntrance& entrance : mSceneEntrances)
        {
            if (entrance.sceneEntranceIndex == SceneManager::GetSceneEntranceIndex())
            {
                for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
                {
                    mSpawnPositions.push_back(entrance.position + entrance.spawnOffset);
                }
                mSpawnDirection = entrance.spawnOffset;
            }
        }
    }

    for (int i = 0; i < PlayerManager::GetCharacterTextures().size(); i++)
    {
        CharacterExploration newCharacter;

        std::string name;
        switch (PlayerManager::GetCharacterAttributes()[i].characterClass)
        {
            case DANCER:
            {
                name = "Dancer";
                break;
            }
            case KNIGHT:
            {
                name = "Knight";
                break;
            }
            case MAGE:
            {
                name = "Mage";
                break;
            }
            case PALADIN:
            {
                name = "Sigurd";
                break;
            }
        }

        newCharacter.SetSpriteSheet(PlayerManager::GetCharacterTextures()[i]);
        newCharacter.LoadAnimations(name);
        newCharacter.SetPosition(mSpawnPositions[i]);
        if (SceneManager::ReturnToOverworld())
            newCharacter.mRigidbody.lastVelocity = SceneManager::GetPreviousDirection(i);
        else
            newCharacter.mRigidbody.lastVelocity = mSpawnDirection;
        newCharacter.mPartyIndex = i;

        mCharacters.push_back(newCharacter);
    }
}

void SceneTown::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTown::Input()
{
    SceneExploration::Input();

    if (mCharacterState == CS_INTERACT_MENU)
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
    }
}

void SceneTown::Update(const float dt)
{
    SceneExploration::Update(dt);

    for (CharacterExploration& character : mCharacters)
    {
        character.UpdateMovement(mMapWidth, mMapHeight, mTiles, mCharacters, dt);
        character.Update(dt);

        if (character.mMovement.stepTaken && character.mPartyIndex == 0)
        {
            for (const SceneEntrance& entrance : mSceneEntrances)
            {
                if (character.GetPosition() == entrance.position)
                {
                    SceneManager::ClearPositionsAndDirections();
                    SceneManager::SetSceneToLoad(OVERWORLD, entrance.sceneEntranceIndex);
                }
            }

            if (SceneManager::GetIsOverworld())
            {
                mStepsUntilEncounter--;
                if (mStepsUntilEncounter <= 0)
                {
                    int index = character.GetPosition().x / TILE_SIZE + (character.GetPosition().y * mMapWidth) / TILE_SIZE;
                    ETerrainType currentTerrain = mTiles[index].terrainType;

                    SceneManager::ClearPositionsAndDirections();
                    for (int i = 0; i < mCharacters.size(); i++)
                    {
                        SceneManager::SetPreviousOverworldPosition(mCharacters[i].GetPosition());
                        SceneManager::SetPreviousDirection(mCharacters[i].mRigidbody.lastVelocity);
                    }
                    SceneManager::SetSceneToLoad(BATTLE, -1, false, currentTerrain, mEnemyEncounters);
                }
            }
        }
    }
}

void SceneTown::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
{
    SceneExploration::Render(renderer, camera);

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

    if (mCharacterState == CS_INTERACT_MENU)
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