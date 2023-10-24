#include "SceneTown.h"

SceneTown::~SceneTown()
{
	
}

void SceneTown::Setup(static SDL_Renderer* renderer)
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
    else if (GameManager::GetSceneEntranceIndex() == -1)
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

    SceneExploration::SetupCharacters();
}

void SceneTown::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTown::Input()
{
    SceneExploration::Input();
}

void SceneTown::Update(const float dt)
{
    SceneExploration::Update(dt);
}

void SceneTown::Render(static SDL_Rect& camera)
{
    SceneExploration::Render(camera);
}