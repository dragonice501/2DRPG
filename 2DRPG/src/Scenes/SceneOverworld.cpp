#include "SceneOverworld.h"

#include <iostream>

SceneOverworld::~SceneOverworld()
{
    
}

void SceneOverworld::Setup(SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    Character sigurd;
    sigurd.Init("Sigurd", "SigurdAnimations", spawnPosition, renderer);
    mCharacters.push_back(sigurd);
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

    for (Character& character : mCharacters)
    {
        character.UpdateMovement(mMapWidth, mMapHeight, mTiles, dt);
        character.Update(dt);

        if (character.mMovement.stepTaken)
        {
            for (const SceneEntrance& entrance : mSceneEntrances)
            {
                if (character.position == entrance.position)
                {
                    SceneManager::Instance().SetSceneToLoad(TOWN, entrance.sceneEntranceIndex);
                }
            }
        }
    }
}

void SceneOverworld::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
    for (Character& character : mCharacters)
    {
        camera.x = character.position.x * TILE_SPRITE_SCALE - (Engine::mWindowWidth / 2);
        camera.y = character.position.y * TILE_SPRITE_SCALE - (Engine::mWindowHeight / 2);

        camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
        camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
    }
    
    SceneExploration::Render(renderer, camera);

    for (Character& character : mCharacters)
    {
        character.Render(renderer);
    }
}