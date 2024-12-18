#include "./Engine.h"

#include "AudioManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"

#include <random>

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
    srand(time(NULL));

    isRunning = GraphicsManager::OpenWindow();
    isRunning = AudioManager::Init();

    AudioManager::SetMasterVolume();

    return isRunning;
}

void Engine::Run()
{
    GameManager::SetSceneToLoad("MainMenu", -1);
    PlayerManager::SetupCharacters();

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

        // Load scene if one is ready
        if (GameManager::SceneReadyToLoad())
        {
            SceneManager::LoadScene();
        }

        // Clear Render
        GraphicsManager::ClearScreen(0xFF000000);

        // Update Input Manager
        InputManager::Update(deltaTime);

        // Game Loop
        SceneManager::CurrentSceneInput();
        SceneManager::CurrentSceneUpdate(deltaTime);
        SceneManager::CurrentSceneRender();

        // Present Render
        GraphicsManager::PresentRender();
    }
}

void Engine::Destroy()
{
    AudioManager::Destroy();
    GraphicsManager::CloseWindow();
}