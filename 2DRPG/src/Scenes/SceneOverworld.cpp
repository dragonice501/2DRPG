#include "SceneOverworld.h"

#include <iostream>

SceneOverworld::~SceneOverworld()
{
    
}

void SceneOverworld::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    if (GameManager::LoadedGame())
    {
        for (int i = 0; i < 4; i++)
        {
            mSpawnPositions.push_back(GameManager::GetPreviousCharacterPosition(i));
            mSpawnDirections.push_back(GameManager::GetPreviousCharacterDirection(i));
        }
    }
    else if (GameManager::NewGame())
    {
        mSpawnPositions.clear();
        mSpawnPositions.push_back(Vec2(16.0f, 17.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(17.0f, 17.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(17.0f, 18.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(16.0f, 18.0f) * TILE_SIZE);

        for (int i = 0; i < 4; i++)
        {
            mSpawnDirections.push_back(Vec2(0.0f, 1.0f));
        }
    }

    GameManager::SetNewGame(false);
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