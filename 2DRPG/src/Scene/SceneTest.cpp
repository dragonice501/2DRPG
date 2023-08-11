#include "SceneTest.h"

SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    // Add the sytems that need to be processed in our game
    registry->AddSystem<RenderSystem>();

    // Adding assets to the asset store
    assetStore->AddTexture(renderer, "TileMap", "./assets/Chapter_0_m.png");

    // Load the tilemap
    int tileSize = 32;
    double tileScale = 2.0;
    int mapNumCols = 25;
    int mapNumRows = 20;

    /*std::fstream mapFile;
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
    Engine::mapHeight = mapNumRows * tileSize * tileScale;*/

    // Create an entity
    Entity tileMap = registry->CreateEntity();
    tileMap.Tag("Sprite");
    tileMap.AddComponent<TransformComponent>(Vec2(0, 0), Vec2(1.0, 1.0), 0.0);
    tileMap.AddComponent<SpriteComponent>("TileMap", 1024, 1024);
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

    // Update the registry to process the entities that are waiting to be created/deleted
    registry->Update();
}

void SceneTest::Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render 
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, Engine::Camera());
}