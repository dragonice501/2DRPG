#include "./Engine.h"

#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../ECS/Systems.h"

#include "../Utils/Vec2.h"

#include "../Scene/Scene.h"
#include "../Scene/ScenePikuma.h"
#include "../Scene/SceneTest.h"

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

    mRegistry = std::make_unique<Registry>();
    mAssetStore = std::make_unique<AssetStore>();
    mEventBus = std::make_unique<EventBus>();
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
    mWindowWidth = 1280;
    mWindowHeight = 720;
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

    // Initialize the ImGui context
    ImGui::CreateContext();
    ImGuiSDL::Initialize(mRenderer, mWindowWidth, mWindowHeight);

    // Initialize the camera view with the entire screen area
    camera.x = 0;
    camera.y = 0;
    camera.w = mWindowWidth;
    camera.h = mWindowHeight;

    //SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
    isRunning = true;

    return true;
}

void Engine::Run()
{
    std::unique_ptr<Scene> scene = std::make_unique<SceneTest>();
    scene->Setup(mRegistry, mAssetStore, mRenderer);

    while (isRunning)
    {
        //std::cout << SDL_GetTicks() - millisecondsPreviousFrame << std::endl;
        int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
        if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME)
        {
            SDL_Delay(timeToWait);
        }

        // The difference in ticks since the last frame, converted to seconds
        double deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0;

        // Store the "previous" frame time
        millisecondsPreviousFrame = SDL_GetTicks();

        scene->Input(mEventBus);
        scene->Update(mRegistry, mEventBus, deltaTime);
        scene->Render(mRegistry, mAssetStore, mRenderer);

        SDL_RenderPresent(mRenderer);
    }
}

void Engine::Destroy()
{
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}