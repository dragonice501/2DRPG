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

int Engine::mWindowWidth;
int Engine::mWindowHeight;
int Engine::mapWidth;
int Engine::mapHeight;
SDL_Rect Engine::camera;
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
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    }
    if (TTF_Init() != 0)
    {
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    mWindowWidth = displayMode.w;
    mWindowHeight = displayMode.h;
    mWindowWidth = 16 * TILE_SIZE * TILE_SPRITE_SCALE;
    mWindowHeight = 9 * TILE_SIZE * TILE_SPRITE_SCALE;
    mWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_BORDERLESS);

    if (!mWindow)
    {
        return false;
    }
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

    if (!mRenderer)
    {
        return false;
    }

    // Initialize the camera view with the entire screen area
    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.w = mWindowWidth;
    camera.h = mWindowHeight;

    //SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
    isRunning = true;

    return true;
}

void Engine::Run()
{
    SceneManager::Instance().SetSceneToLoad(OVERWORLD, 0);

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

        InputManager::Input(deltaTime);

        // Load Scene if one is ready
        if (SceneManager::Instance().SceneReadyToLoad())
        {
            if (SceneManager::Instance().CurrentScene())
            {
                SceneManager::Instance().CurrentSceneShutdown();
            }
            SceneManager::Instance().LoadScene(mRenderer);
        }

        // Game Loop
        SceneManager::Instance().CurrentSceneInput();
        SceneManager::Instance().CurrentSceneUpdate(deltaTime);
        SceneManager::Instance().CurrentSceneRender(mRenderer);

        SDL_RenderPresent(mRenderer);
    }
}

void Engine::Destroy()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}