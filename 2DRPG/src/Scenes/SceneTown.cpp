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

    mDancer.Init("Dancer", "DancerAnimations", Vec2(16 * TILE_SIZE, 14 * TILE_SIZE), renderer);
    mSigurd.Init("Sigurd", "SigurdAnimations", Vec2(17 * TILE_SIZE, 17 * TILE_SIZE), renderer);
}

void SceneTown::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTown::Input()
{
    SceneExploration::Input(mSigurd);
}

void SceneTown::Update(const float dt)
{
    SceneExploration::Update(dt);

    mDancer.Update(dt);

    mSigurd.UpdateMovement(mMapWidth, mMapHeight, mTiles, dt);
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

void SceneTown::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
    camera.x = mSigurd.GetPosition().x * TILE_SPRITE_SCALE - (Engine::mWindowWidth / 2);
    camera.y = mSigurd.GetPosition().y * TILE_SPRITE_SCALE - (Engine::mWindowHeight / 2);

    camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
    camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);

    SceneExploration::Render(renderer, camera);

    mDancer.Render(renderer);
    mSigurd.Render(renderer);
}