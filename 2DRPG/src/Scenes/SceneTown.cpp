#include "SceneTown.h"

SceneTown::~SceneTown()
{
	SDL_DestroyTexture(mSpriteSheet);
}

void SceneTown::Setup(SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    for (const SceneEntrance& entrance : mSceneEntrances)
    {
        if (entrance.sceneEntranceIndex == SceneManager::Instance().GetSceneEntranceIndex())
        {
            spawnPosition = entrance.position + entrance.spawnOffset;
        }
    }
    
    if (SceneManager::Instance().GetSceneEntranceIndex() == -1)
    {
        spawnPosition = { 16 * TILE_SIZE, 16 * TILE_SIZE };
    }

    /*Character newCharacter;
    newCharacter.Init("Sigurd", "SigurdAnimations", Vec2(16 * TILE_SIZE, 14 * TILE_SIZE), renderer);
    mCharacters.push_back(newCharacter);*/

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
        if (mSigurd.GetCharacterState() != CS_INTERACTING)
        {
            Vec2 position = mSigurd.GetPosition() + mSigurd.mRigidbody.lastVelocity;
            for (Actor& actor : mActors)
            {
                if (position == actor.GetPosition())
                {
                    std::cout << "interaction made at " << position.x << ',' << position.y << std::endl;
                    mSigurd.SetCharacterState(CS_INTERACTING);
                }
            }
        }
        else
        {
            mSigurd.SetCharacterState(CS_MOVING);
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

    if (mSigurd.GetCharacterState() == CS_MOVING)
    {
        mSigurd.UpdateMovement(mMapWidth, mMapHeight, mTiles, mActors, dt);
        mSigurd.Update(dt);

        if (mSigurd.mMovement.stepTaken)
        {
            for (const SceneEntrance& entrance : mSceneEntrances)
            {
                if (mSigurd.GetPosition() == entrance.position)
                {
                    SceneManager::Instance().SetSceneToLoad(OVERWORLD, entrance.sceneEntranceIndex);
                }
            }
        }
    }

    /*for (Character& character : mCharacters)
    {
        character.UpdateMovement(mMapWidth, mMapHeight, mTiles, mActors, dt);
        character.Update(dt);
    }*/
}

void SceneTown::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
    camera.x = mSigurd.GetPosition().x * TILE_SPRITE_SCALE - (Engine::mWindowWidth / 2);
    camera.y = mSigurd.GetPosition().y * TILE_SPRITE_SCALE - (Engine::mWindowHeight / 2);

    camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
    camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);

    SceneExploration::Render(renderer, camera);

    for (Actor& actor : mActors)
    {
        actor.Render(renderer);
    }

    /*for (Character& character : mCharacters)
    {
        character.Render(renderer);
    }*/

    mSigurd.Render(renderer);
}