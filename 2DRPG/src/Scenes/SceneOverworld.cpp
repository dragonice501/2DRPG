#include "SceneOverworld.h"

#include <iostream>

SceneOverworld::~SceneOverworld()
{
    
}

void SceneOverworld::Setup(static SDL_Renderer* renderer)
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

void SceneOverworld::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneOverworld::Input()
{
    SceneExploration::Input();
}

void SceneOverworld::Update(const float dt)
{
    SceneExploration::Update(dt);

    if (mExplorationState == ES_MENUING) return;

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
                    SceneManager::SetSceneToLoad(TOWN, entrance.sceneEntranceIndex);
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

void SceneOverworld::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
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

    if (mExplorationState == ES_MENUING)
    {
        DrawPartyMenu(renderer);
    }
}