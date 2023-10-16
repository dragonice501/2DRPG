#include "SceneTownShop.h"

SceneTownShop::~SceneTownShop()
{
}

void SceneTownShop::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    if (GameManager::GetSceneEntranceIndex() == -1)
    {
        mSpawnPositions.clear();
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);

        for (int i = 0; i < 4; i++)
        {
            mSpawnDirections.push_back(Vec2(0.0f, 1.0f));
        }
    }

    SceneTownShop::SetupCharacters();
}

void SceneTownShop::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTownShop::Input()
{
    SceneExploration::Input();
}

void SceneTownShop::Update(const float dt)
{
    SceneExploration::Update(dt);
}

void SceneTownShop::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
{
    SceneExploration::Render(renderer, camera);
}