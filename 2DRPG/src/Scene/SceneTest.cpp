#include "SceneTest.h"

#include <iostream>

SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    // Add the sytems that need to be processed in our game
    registry->AddSystem<RenderTileSystem>();
    registry->AddSystem<RenderCharacterSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<KeyboardControlSystem>();
    registry->AddSystem<MovementSystem>();

    // Adding assets to the asset store
    assetStore->AddTexture(renderer, "TileMap", "./assets/Chapter_0_m.png");
    assetStore->AddTexture(renderer, "SigurdSheet", "./assets/Sigurd.png");

    int tileType;
    int i = 0;
    int mapWidth = 0;
    int mapHeight = 0;
    float mapXOffset = 0;
    float mapYOffset = 0;

    std::ifstream file("./assets/MapSaveFile.txt");
    std::string type;
    while (file >> type)
    {
        if (type == ":width")
        {
            file >> mapWidth;
        }
        else if (type == ":height")
        {
            file >> mapHeight;
        }
        else if (type == ":xOffset")
        {
            file >> mapXOffset;
        }
        else if (type == ":yOffset")
        {
            file >> mapYOffset;
        }
        else if (type == ":tile")
        {
            file >> tileType;

            int x = (tileType % 28);
            int y = (tileType / 28);

            Entity tile = registry->CreateEntity();
            tile.Tag("Tile");
            tile.AddComponent<TransformComponent>(Vec2((i % mapWidth) * 16, (i / mapHeight) * 16), Vec2(1.0, 1.0), 0.0);
            tile.AddComponent<SpriteComponent>("TileMap", 16, 16, 0, false, x * 16, y * 16);
            tile.AddComponent<TileComponent>();
            i++;
        }
    }

    Entity sigurd = registry->CreateEntity();
    sigurd.Tag("player");
    sigurd.AddComponent<TransformComponent>(Vec2(0, 0), Vec2(1.0, 1.0), 0.0);
    sigurd.AddComponent<SpriteComponent>("SigurdSheet", 32, 32, 0);
    sigurd.AddComponent<AnimationComponent>(4, 4, true);
    sigurd.AddComponent<KeyboardControlComponent>(Vec2(0.0f, -16.0f), Vec2(0.0f, 16.0f), Vec2(-16.0f, 0.0f), Vec2(16.0f, 0.0f));
    sigurd.AddComponent<RigidbodyComponent>();
}

void SceneTest::Input(std::unique_ptr<EventBus>& eventBus)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // Handle core SDL events (close window, key pressed, etc.)
        switch (sdlEvent.type)
        {
            case SDL_KEYDOWN:
            {
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) Engine::SetIsRunning(false);

                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
                break;
            }
        }
    }
}

void SceneTest::Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt)
{
    // Reset all event handlers for the current frame
    eventBus->Reset();
    registry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(eventBus);

    // Update the registry to process the entities that are waiting to be created/deleted
    registry->Update();
    registry->GetSystem<MovementSystem>().Update(dt);
    registry->GetSystem<AnimationSystem>().Update(dt);
}

void SceneTest::Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render 
    registry->GetSystem<RenderTileSystem>().Update(renderer, assetStore, Engine::Camera());
    registry->GetSystem<RenderCharacterSystem>().Update(renderer, assetStore, Engine::Camera());
}