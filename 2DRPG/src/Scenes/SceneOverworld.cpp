#include "SceneOverworld.h"

#include <iostream>

SceneOverworld::~SceneOverworld()
{
    
}

void SceneOverworld::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    if (GameManager::GetSceneEntranceIndex() == -1)
    {
        mSpawnPositions.clear();
        mSpawnPositions.push_back(Vec2(39.0f, 32.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(40.0f, 32.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(40.0f, 33.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(39.0f, 33.0f) * TILE_SIZE);

        for (int i = 0; i < 4; i++)
        {
            mSpawnDirections.push_back(Vec2(0.0f, 1.0f));
        }
    }

    SceneExploration::SetupCharacters();
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
}

void SceneOverworld::Render(static SDL_Rect& camera)
{ 
    SceneExploration::Render(camera);
}