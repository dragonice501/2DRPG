#include "./Engine.h"

#include "../Utils/Vec2.h"

#include "../Managers/SceneManager.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneOverworld.h"

#include "../Managers/InputManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>

#include <fstream>

bool Engine::isRunning;

Engine::Engine()
{
    isRunning = false;
    isDebug = false;
}

void Engine::SetIsRunning(const bool running)
{
    isRunning = running;
}

bool Engine::Init()
{
    isRunning = GraphicsManager::OpenWindow();;

    return true;
}

void Engine::Run()
{
    SceneManager::SetSceneToLoad(TOWN, -1);

    while (isRunning)
    {
        // Calculate Delta Time
        int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
        if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME)
        {
            SDL_Delay(timeToWait);
        }

        double deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0;
        if (deltaTime > MILLISECONDS_PER_FRAME) deltaTime = MILLISECONDS_PER_FRAME;

        millisecondsPreviousFrame = SDL_GetTicks();

        // Load Scene if one is ready
        if (SceneManager::SceneReadyToLoad())
        {
            if (SceneManager::CurrentScene())
            {
                SceneManager::CurrentSceneShutdown();
            }
            SceneManager::LoadScene();
        }

        // Update Input Manager
        InputManager::Update(deltaTime);

        // Game Loop
        SceneManager::CurrentSceneInput();
        SceneManager::CurrentSceneUpdate(deltaTime);
        SceneManager::CurrentSceneRender();

        GraphicsManager::PresentRender();
    }
}

void Engine::Destroy()
{
    GraphicsManager::CloseWindow();
}