#include "./Engine.h"
#include "../ECS/ECS.h"

#include "../Components/Components.h"

#include "../Systems/Systems.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm/glm.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>

#include <fstream>

int Engine::mWindowWidth;
int Engine::mWindowHeight;
int Engine::mapWidth;
int Engine::mapHeight;

Engine::Engine()
{
    isRunning = false;
    isDebug = false;

    mRegistry = std::make_unique<Registry>();
    mAssetStore = std::make_unique<AssetStore>();
    mEventBus = std::make_unique<EventBus>();
}

Engine::~Engine()
{
    
}

void Engine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return;
    }
    if (TTF_Init() != 0)
    {
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    mWindowWidth = displayMode.w;
    mWindowHeight = displayMode.h;
    mWindowWidth = 800;
    mWindowHeight = 800;
    mWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_BORDERLESS);

    if (!mWindow)
    {
        return;
    }
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

    if (!mRenderer)
    {
        return;
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
}

void Engine::Run()
{
    Setup();

    while (isRunning)
    {
        Input();
        Update();
        Draw();
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

void Engine::Setup()
{
    // Add the sytems that need to be processed in our game
    mRegistry->AddSystem<MovementSystem>();
    mRegistry->AddSystem<RenderSystem>();
    mRegistry->AddSystem<AnimationSystem>();
    mRegistry->AddSystem<CollisionSystem>();
    mRegistry->AddSystem<RenderCollisionSystem>();
    mRegistry->AddSystem<DamageSystem>();
    mRegistry->AddSystem<KeyboardControlSystem>();
    mRegistry->AddSystem<CameraMovementSystem>();
    mRegistry->AddSystem<ProjectileEmitSystem>();
    mRegistry->AddSystem<ProjectileSystem>();
    mRegistry->AddSystem<RenderTextSystem>();
    mRegistry->AddSystem<RenderHealthBarSystem>();
    mRegistry->AddSystem<RenderGUISytem>();

    // Adding assets to the asset store
    mAssetStore->AddTexture(mRenderer, "tank-image", "./assets/images/tank-panther-right.png");
    mAssetStore->AddTexture(mRenderer, "truck-image", "./assets/images/truck-ford-right.png");
    mAssetStore->AddTexture(mRenderer, "tree-image", "./assets/images/tree.png");
    mAssetStore->AddTexture(mRenderer, "chopper-image", "./assets/images/chopper-spritesheet.png");
    mAssetStore->AddTexture(mRenderer, "radar-image", "./assets/images/radar.png");
    mAssetStore->AddTexture(mRenderer, "tilemap-image", "./assets/tilemaps/jungle.png");
    mAssetStore->AddTexture(mRenderer, "bullet-image", "./assets/images/bullet.png");
    mAssetStore->AddFont("charriot-font-20", "./assets/fonts/charriot.ttf", 20);
    mAssetStore->AddFont("pico8-font-5", "./assets/fonts/pico8.ttf", 5);
    mAssetStore->AddFont("pico8-font-10", "./assets/fonts/pico8.ttf", 10);

    // Load the tilemap
    int tileSize = 32;
    double tileScale = 2.0;
    int mapNumCols = 25;
    int mapNumRows = 20;

    std::fstream mapFile;
    mapFile.open("./assets/tilemaps/jungle.map");

    for (int y = 0; y < mapNumRows; y++)
    {
        for (int x = 0; x < mapNumCols; x++)
        {
            char ch;
            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * tileSize;
            mapFile.ignore();

            Entity tile = mRegistry->CreateEntity();
            tile.Group("tiles");
            tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
            tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
        }
    }
    mapFile.close();
    mapWidth = mapNumCols * tileSize * tileScale;
    mapHeight = mapNumRows * tileSize * tileScale;

    // Create an entity
    Entity chopper = mRegistry->CreateEntity();
    chopper.Tag("player");
    chopper.AddComponent<TransformComponent>(glm::vec2(240.0, 110.0), glm::vec2(1.0, 1.0), 0.0);
    chopper.AddComponent<RigidbodyComponent>(glm::vec2(0.0, 0.0));
    chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 5);
    chopper.AddComponent<AnimationComponent>(2, 15, true);
    chopper.AddComponent<BoxColliderComponent>(32, 25, glm::vec2(0, 5));
    chopper.AddComponent<ProjectileEmitterComponent>(glm::vec2(150.0, 150.0), 0, 10000, 10, true);
    chopper.AddComponent<KeyboardControlComponent>(glm::vec2(0, -50), glm::vec2(50, 0), glm::vec2(0, 50), glm::vec2(-50, 0));
    chopper.AddComponent<CameraFollowComponent>();
    chopper.AddComponent<HealthComponent>(100);

    Entity radar = mRegistry->CreateEntity();
    radar.AddComponent<TransformComponent>(glm::vec2(mWindowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    radar.AddComponent<RigidbodyComponent>(glm::vec2(0.0, 0.0));
    radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 9, true);
    radar.AddComponent<AnimationComponent>(8, 5, true);

    Entity tank = mRegistry->CreateEntity();
    tank.Group("enemies");
    tank.AddComponent<TransformComponent>(glm::vec2(500.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    tank.AddComponent<RigidbodyComponent>(glm::vec2(20.0, 0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1);
    tank.AddComponent<BoxColliderComponent>(25, 18, glm::vec2(5, 7));
    tank.AddComponent<HealthComponent>(100);

    Entity truck = mRegistry->CreateEntity();
    truck.Group("enemies");
    truck.AddComponent<TransformComponent>(glm::vec2(120.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    truck.AddComponent<RigidbodyComponent>(glm::vec2(0.0, 0.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 1);
    truck.AddComponent<BoxColliderComponent>(25, 20, glm::vec2(5, 5));
    truck.AddComponent<ProjectileEmitterComponent>(glm::vec2(0.0, -100.0), 2000, 5000, 10, false);
    truck.AddComponent<HealthComponent>(100);

    Entity treeA = mRegistry->CreateEntity();
    treeA.Group("obstacles");
    treeA.AddComponent<TransformComponent>(glm::vec2(600.0, 495.0), glm::vec2(1.0, 1.0), 0.0);
    treeA.AddComponent<SpriteComponent>("tree-image", 16, 32, 2);
    treeA.AddComponent<BoxColliderComponent>(16, 32);

    Entity treeB = mRegistry->CreateEntity();
    treeB.Group("obstacles");
    treeB.AddComponent<TransformComponent>(glm::vec2(400.0, 495.0), glm::vec2(1.0, 1.0), 0.0);
    treeB.AddComponent<SpriteComponent>("tree-image", 16, 32, 2);
    treeB.AddComponent<BoxColliderComponent>(16, 32);

    Entity label = mRegistry->CreateEntity();
    SDL_Color green = { 0, 255, 0 };
    label.AddComponent<TextLabelComponent>(glm::vec2(mWindowWidth / 2 - 40, 10), "CHOPPER 1.0", "pico8-font-10", green, true);
}

void Engine::Input()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // ImGui SDL input
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        ImGuiIO& io = ImGui::GetIO();
        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.MousePos = ImVec2(mouseX, mouseY);
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

        // Handle core SDL events (close window, key pressed, etc.)
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            if (sdlEvent.key.keysym.sym == SDLK_F1) {
                isDebug = !isDebug;
            }
            mEventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
            break;
        }
    }
}

void Engine::Update()
{
    // If we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
    int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0;

    // Store the "previous" frame time
    millisecondsPreviousFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    mEventBus->Reset();

    // Perform the subscription of the events for all systems
    mRegistry->GetSystem<MovementSystem>().SubscribeToEvents(mEventBus);
    mRegistry->GetSystem<DamageSystem>().SuscribeToEvents(mEventBus);
    mRegistry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(mEventBus);
    mRegistry->GetSystem<ProjectileEmitSystem>().SubcribeToEvents(mEventBus);

    // Update the mRegistry to process the entities that are waiting to be created/deleted
    mRegistry->Update();

    // Invoke all the systems that need to update 
    mRegistry->GetSystem<MovementSystem>().Update(deltaTime);
    mRegistry->GetSystem<AnimationSystem>().Update(deltaTime);
    mRegistry->GetSystem<CollisionSystem>().Update(mEventBus);
    mRegistry->GetSystem<ProjectileEmitSystem>().Update(mRegistry);
    mRegistry->GetSystem<CameraMovementSystem>().Update(camera);
    mRegistry->GetSystem<ProjectileSystem>().Update();
}

void Engine::Draw()
{
    SDL_SetRenderDrawColor(mRenderer, 21, 21, 21, 255);
    SDL_RenderClear(mRenderer);

    // Invoke all the systems that need to render 
    mRegistry->GetSystem<RenderSystem>().Update(mRenderer, mAssetStore, camera);
    mRegistry->GetSystem<RenderTextSystem>().Update(mRenderer, mAssetStore, camera);
    mRegistry->GetSystem<RenderHealthBarSystem>().Update(mRenderer, mAssetStore, camera);
    if (isDebug)
    {
        mRegistry->GetSystem<RenderCollisionSystem>().Update(mRenderer, camera);
        mRegistry->GetSystem<RenderGUISytem>().Update(mRegistry, camera);
    }

    SDL_RenderPresent(mRenderer);
}