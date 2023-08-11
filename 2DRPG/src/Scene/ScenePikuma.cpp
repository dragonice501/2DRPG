#include "ScenePikuma.h"

ScenePikuma::ScenePikuma()
{
}

ScenePikuma::~ScenePikuma()
{
}

void ScenePikuma::Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    // Add the sytems that need to be processed in our game
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<RenderCollisionSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<KeyboardControlSystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<ProjectileEmitSystem>();
    registry->AddSystem<ProjectileSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<RenderHealthBarSystem>();
    registry->AddSystem<RenderGUISytem>();

    // Adding assets to the asset store
    assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "tree-image", "./assets/images/tree.png");
    assetStore->AddTexture(renderer, "chopper-image", "./assets/images/chopper-spritesheet.png");
    assetStore->AddTexture(renderer, "radar-image", "./assets/images/radar.png");
    assetStore->AddTexture(renderer, "tilemap-image", "./assets/tilemaps/jungle.png");
    assetStore->AddTexture(renderer, "bullet-image", "./assets/images/bullet.png");
    assetStore->AddFont("charriot-font-20", "./assets/fonts/charriot.ttf", 20);
    assetStore->AddFont("pico8-font-5", "./assets/fonts/pico8.ttf", 5);
    assetStore->AddFont("pico8-font-10", "./assets/fonts/pico8.ttf", 10);

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

            Entity tile = registry->CreateEntity();
            tile.Group("tiles");
            tile.AddComponent<TransformComponent>(Vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), Vec2(tileScale, tileScale), 0.0);
            tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
        }
    }
    mapFile.close();
    Engine::mapWidth = mapNumCols * tileSize * tileScale;
    Engine::mapHeight = mapNumRows * tileSize * tileScale;

    // Create an entity
    Entity chopper = registry->CreateEntity();
    chopper.Tag("player");
    chopper.AddComponent<TransformComponent>(Vec2(240.0, 110.0), Vec2(1.0, 1.0), 0.0);
    chopper.AddComponent<RigidbodyComponent>(Vec2(0.0, 0.0));
    chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 5);
    chopper.AddComponent<AnimationComponent>(2, 15, true);
    chopper.AddComponent<BoxColliderComponent>(32, 25, Vec2(0, 5));
    chopper.AddComponent<ProjectileEmitterComponent>(Vec2(150.0, 150.0), 0, 10000, 10, true);
    chopper.AddComponent<KeyboardControlComponent>(Vec2(0, -50), Vec2(50, 0), Vec2(0, 50), Vec2(-50, 0));
    chopper.AddComponent<CameraFollowComponent>();
    chopper.AddComponent<HealthComponent>(100);

    Entity radar = registry->CreateEntity();
    radar.AddComponent<TransformComponent>(Vec2(Engine::mWindowWidth - 74, 10.0), Vec2(1.0, 1.0), 0.0);
    radar.AddComponent<RigidbodyComponent>(Vec2(0.0, 0.0));
    radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 9, true);
    radar.AddComponent<AnimationComponent>(8, 5, true);

    Entity tank = registry->CreateEntity();
    tank.Group("enemies");
    tank.AddComponent<TransformComponent>(Vec2(500.0, 500.0), Vec2(1.0, 1.0), 0.0);
    tank.AddComponent<RigidbodyComponent>(Vec2(20.0, 0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1);
    tank.AddComponent<BoxColliderComponent>(25, 18, Vec2(5, 7));
    tank.AddComponent<HealthComponent>(100);

    Entity truck = registry->CreateEntity();
    truck.Group("enemies");
    truck.AddComponent<TransformComponent>(Vec2(120.0, 500.0), Vec2(1.0, 1.0), 0.0);
    truck.AddComponent<RigidbodyComponent>(Vec2(0.0, 0.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 1);
    truck.AddComponent<BoxColliderComponent>(25, 20, Vec2(5, 5));
    truck.AddComponent<ProjectileEmitterComponent>(Vec2(0.0, -100.0), 2000, 5000, 10, false);
    truck.AddComponent<HealthComponent>(100);

    Entity treeA = registry->CreateEntity();
    treeA.Group("obstacles");
    treeA.AddComponent<TransformComponent>(Vec2(600.0, 495.0), Vec2(1.0, 1.0), 0.0);
    treeA.AddComponent<SpriteComponent>("tree-image", 16, 32, 2);
    treeA.AddComponent<BoxColliderComponent>(16, 32);

    Entity treeB = registry->CreateEntity();
    treeB.Group("obstacles");
    treeB.AddComponent<TransformComponent>(Vec2(400.0, 495.0), Vec2(1.0, 1.0), 0.0);
    treeB.AddComponent<SpriteComponent>("tree-image", 16, 32, 2);
    treeB.AddComponent<BoxColliderComponent>(16, 32);

    Entity label = registry->CreateEntity();
    SDL_Color green = { 0, 255, 0 };
    label.AddComponent<TextLabelComponent>(Vec2(Engine::mWindowWidth / 2 - 40, 10), "CHOPPER 1.0", "pico8-font-10", green, true);
}

void ScenePikuma::Input(std::unique_ptr<EventBus>& eventBus)
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
            case SDL_KEYDOWN:
            {
                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
                break;
            }
        }
    }
}

void ScenePikuma::Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt)
{
    // Reset all event handlers for the current frame
    eventBus->Reset();

    // Perform the subscription of the events for all systems
    registry->GetSystem<MovementSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<DamageSystem>().SuscribeToEvents(eventBus);
    registry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().SubcribeToEvents(eventBus);

    // Update the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    // Invoke all the systems that need to update 
    registry->GetSystem<MovementSystem>().Update(dt);
    registry->GetSystem<AnimationSystem>().Update(dt);
    registry->GetSystem<CollisionSystem>().Update(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<CameraMovementSystem>().Update(Engine::Camera());
    registry->GetSystem<ProjectileSystem>().Update();
}

void ScenePikuma::Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render 
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, Engine::Camera());
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, Engine::Camera());
    registry->GetSystem<RenderHealthBarSystem>().Update(renderer, assetStore, Engine::Camera());
}