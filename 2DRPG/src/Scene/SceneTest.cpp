#include "SceneTest.h"

#include <iostream>

SceneTest::SceneTest() : SceneTest(0, 0)
{
}

SceneTest::SceneTest(const int x, const int y)
{
    startX = x * TILE_SIZE;
    startY = y * TILE_SIZE;
}

SceneTest::~SceneTest()
{
}

void SceneTest::Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    // Add the sytems that need to be processed in our game
    registry->AddSystem<RenderTileSystem>();
    registry->AddSystem<RenderCharacterSystem>();
    registry->AddSystem<CharacterAnimationSystem>();
    registry->AddSystem<CharacterInputSystem>();
    registry->AddSystem<CharacterMovementSystem>();
    registry->AddSystem<CameraMovementSystem>();

    registry->AddSystem<WorldCollisionSystem>();
    registry->AddSystem<WorldEncounterSystem>();

    // Adding assets to the asset store
    assetStore->AddTexture(renderer, "TileMap", "./assets/Chapter_0_m.png");
    assetStore->AddTexture(renderer, "BarbarianSheet", "./assets/Barbarian.png");
    assetStore->AddTexture(renderer, "BowFighterSheet", "./assets/Bow_Fighter.png");
    assetStore->AddTexture(renderer, "DancerSheet", "./assets/Dancer.png");
    assetStore->AddTexture(renderer, "MageSheet", "./assets/Mage.png");
    assetStore->AddTexture(renderer, "SigurdSheet", "./assets/Sigurd.png");
    assetStore->AddTexture(renderer, "SwordArmourSheet", "./assets/Sword_Armour.png");
    assetStore->AddTexture(renderer, "FighterSheet", "./assets/Fighter.png");

    int tileType;
    int i = 0;
    float mapXOffset = 0;
    float mapYOffset = 0;

    std::ifstream file("./assets/MapSaveFile.txt");
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mapWidth >> mapHeight;

            Engine::mapWidth = mapWidth;
            Engine::mapHeight = mapHeight;
        }
        else if (type == "StartPosition")
        {
            file >> startX >> startY;
            startX *= TILE_SIZE;
            startY *= TILE_SIZE;
        }
        else if (type == "SceneEntrance")
        {
            int sceneName;
            int sceneEntranceIndex;
            int sceneEntrancePosX;
            int sceneEntrancePosY;
            file >> sceneName >> sceneEntranceIndex >> sceneEntrancePosX >> sceneEntrancePosY;

            Entity sceneEntrance = registry->CreateEntity();
            sceneEntrance.Tag("Entrance");
            sceneEntrance.AddComponent<SceneEntranceComponent>(sceneName, sceneEntranceIndex, Vec2(sceneEntrancePosX, sceneEntrancePosY));
        }
        else if (type == "Tile")
        {
            file >> tileType;

            int x = (tileType % SPRITE_SHEET_SIZE);
            int y = (tileType / SPRITE_SHEET_SIZE);

            Entity tile = registry->CreateEntity();
            tile.Tag("Tile");
            tile.AddComponent<TransformComponent>(Vec2((i % mapWidth) * TILE_SIZE, (i / mapWidth) * TILE_SIZE), Vec2(1.0, 1.0), 0.0);
            tile.AddComponent<SpriteComponent>("TileMap", TILE_SIZE, TILE_SIZE, 0, 0, 0, false, x * TILE_SIZE, y * TILE_SIZE);
            tile.AddComponent<TileComponent>(x + y * SPRITE_SHEET_SIZE);
            i++;
        }
    }

    Entity sigurd = registry->CreateEntity();
    sigurd.Tag("player");
    sigurd.AddComponent<TransformComponent>(Vec2(startX, startY), Vec2(1.0, 1.0), 0.0);
    sigurd.AddComponent<SpriteComponent>("SigurdSheet", 32, 32, 0, -TILE_SIZE, 1);
    sigurd.AddComponent<AnimationComponent>(4, 8, true);
    sigurd.AddComponent<CharacterInputComponent>();
    sigurd.AddComponent<RigidbodyComponent>();
    sigurd.AddComponent<CharacterMovementComponent>();
    sigurd.AddComponent<CameraFollowComponent>();
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
            case SDL_KEYUP:
            {
                eventBus->EmitEvent<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
                break;
            }
        }
    }
}

void SceneTest::Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt)
{
    // Reset all event handlers for the current frame
    eventBus->Reset();

    registry->GetSystem<CharacterInputSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<WorldCollisionSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<WorldEncounterSystem>().SubscribeToEvents(eventBus);

    // Update the registry to process the entities that are waiting to be created/deleted
    registry->Update();
    registry->GetSystem<CharacterMovementSystem>().Update(dt, eventBus, mapWidth, mapHeight, registry->GetSystem<RenderTileSystem>().GetSystemEntities());
    registry->GetSystem<CameraMovementSystem>().Update(Engine::Camera(), mapWidth, mapHeight);

    registry->GetSystem<CharacterAnimationSystem>().Update(dt);
}

void SceneTest::Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render 
    registry->GetSystem<RenderTileSystem>().Update(renderer, assetStore, Engine::Camera());
    registry->GetSystem<RenderCharacterSystem>().Update(renderer, assetStore, Engine::Camera());
}