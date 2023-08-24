#include "SceneTown.h"

#include "../Systems/WorldCollisionSystem.h"
#include "../Systems/WorldEncounterSystem.h"
#include "../Systems/CharacterMovementSystem.h"

SceneTown::SceneTown()
{
}

SceneTown::~SceneTown()
{
}

void SceneTown::Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    // Add the sytems that need to be processed in our game
    registry->AddSystem<RenderTileSystem>();
    registry->AddSystem<RenderCharacterSystem>();
    registry->AddSystem<CharacterAnimationSystem>();
    registry->AddSystem<CharacterInputSystem>();
    registry->AddSystem<CharacterInteractSystem>();
    registry->AddSystem<CharacterMovementSystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<InteractSystem>();
    registry->AddSystem<WorldCollisionSystem>();
    registry->AddSystem<WorldEncounterSystem>();

    // Adding assets to the asset store
    assetStore->AddTexture(renderer, "TileMap", "./assets/TownSpriteSheet.png");

    int i = 0;

    std::ifstream file("./assets/TownSaveFile.txt");
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mapWidth >> mapHeight;

            Engine::mapWidth = mapWidth;
            Engine::mapHeight = mapHeight;
        }
        else if (type == "Interactable")
        {
            int xPos;
            int yPos;

            file >> xPos >> yPos;

            Entity interactable = registry->CreateEntity();
            interactable.Tag("Interactable");
            interactable.AddComponent<TransformComponent>(Vec2(xPos * TILE_SIZE, yPos * TILE_SIZE), Vec2(1.0f, 1.0f), 0.0f);
            interactable.AddComponent<InteractableComponent>();
        }
        else if (type == "SceneEntrance")
        {
            int sceneName;
            int sceneEntranceIndex;
            int sceneEntrancePosX;
            int sceneEntrancePosY;
            file >> sceneName >> sceneEntranceIndex >> sceneEntrancePosX >> sceneEntrancePosY;

            if (sceneEntranceIndex == SceneManager::GetSceneEntranceIndex())
            {
                spawnPosition = Vec2(sceneEntrancePosX, sceneEntrancePosY) * TILE_SIZE;
            }

            Entity sceneEntrance = registry->CreateEntity();
            sceneEntrance.Tag("Entrance");
            sceneEntrance.AddComponent<SceneEntranceComponent>(sceneName, sceneEntranceIndex, Vec2(sceneEntrancePosX, sceneEntrancePosY));
        }
        else if (type == "Tile")
        {
            int tileType;
            file >> tileType;

            int x = (tileType % SPRITE_SHEET_SIZE);
            int y = (tileType / SPRITE_SHEET_SIZE);

            Entity tile = registry->CreateEntity();
            tile.Tag("Tile");
            tile.AddComponent<TransformComponent>(Vec2((i % mapWidth) * TILE_SIZE, (i / mapWidth) * TILE_SIZE), Vec2(1.0, 1.0), 0.0);
            tile.AddComponent<SpriteComponent>("TileMap", TILE_SIZE, TILE_SIZE, 0, 0, 0, false, x * TILE_SIZE, y * TILE_SIZE);
            tile.AddComponent<TileComponent>(x + y * SPRITE_SHEET_SIZE, true);
            i++;
        }
    }

    assetStore->AddTexture(renderer, "DancerIdleSheet", "./assets/Dancer_Idle.png");

    Entity dancer = registry->CreateEntity();
    dancer.Tag("npc");
    dancer.AddComponent<TransformComponent>(Vec2(16.0f, 14.0f) * TILE_SIZE, Vec2(1.0, 1.0), 0.0);
    dancer.AddComponent<SpriteComponent>("DancerIdleSheet", 32, 32, 0, -22, 1);
    dancer.AddComponent<RigidbodyComponent>(Vec2(0.0f), Vec2(0.0f, 1.0f));
    dancer.AddComponent<InteractableComponent>();
    dancer.AddComponent<BoxColliderAAComponent>();

    dancer.AddComponent<AnimationSystemComponent>();
    dancer.AddComponent<AnimationStateComponent>();
    AnimationSystemComponent::Animation dancerIdle(4, 4, true, "DancerIdleSheet");
    dancer.GetComponent<AnimationSystemComponent>().AddAnimation("Idle", dancerIdle);

    if (spawnPosition == Vec2(0.0f, 0.0f))
    {
        spawnPosition = Vec2(41.0f * TILE_SIZE, 18.0f * TILE_SIZE);
    }

    assetStore->AddTexture(renderer, "SigurdIdleSheet", "./assets/Sigurd_Idle.png");
    assetStore->AddTexture(renderer, "SigurdMovingSheet", "./assets/Sigurd_Moving.png");

    Entity sigurd = registry->CreateEntity();
    sigurd.Tag("player");
    sigurd.AddComponent<TransformComponent>(Vec2(16.0f, 17.0f) * TILE_SIZE, Vec2(1.0, 1.0), 0.0);
    sigurd.AddComponent<SpriteComponent>("SigurdIdleSheet", 32, 32, 0, -22, 1);

    sigurd.AddComponent<AnimationStateComponent>();
    sigurd.AddComponent<AnimationSystemComponent>();
    AnimationSystemComponent::Animation idleAnimation(4, 4, true, "SigurdIdleSheet");
    AnimationSystemComponent::Animation movingAnimation(4, 8, true, "SigurdMovingSheet");
    sigurd.GetComponent<AnimationSystemComponent>().AddAnimation("Idle", idleAnimation);
    sigurd.GetComponent<AnimationSystemComponent>().AddAnimation("Moving", movingAnimation);

    sigurd.AddComponent<CharacterInputComponent>();
    sigurd.AddComponent<RigidbodyComponent>();
    sigurd.AddComponent<CharacterMovementComponent>();
    sigurd.AddComponent<CameraFollowComponent>();
}

void SceneTown::Shutdown(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    registry->KillAllEntities();
    registry->Update();

    registry->RemoveSystem<RenderTileSystem>(registry->GetSystem<RenderTileSystem>());
    registry->RemoveSystem<RenderCharacterSystem>(registry->GetSystem<RenderCharacterSystem>());
    registry->RemoveSystem<CharacterAnimationSystem>(registry->GetSystem<CharacterAnimationSystem>());
    registry->RemoveSystem<CharacterInputSystem>(registry->GetSystem<CharacterInputSystem>());
    registry->RemoveSystem<CharacterMovementSystem>(registry->GetSystem<CharacterMovementSystem>());
    registry->RemoveSystem<CameraMovementSystem>(registry->GetSystem<CameraMovementSystem>());
    registry->RemoveSystem<WorldCollisionSystem>(registry->GetSystem<WorldCollisionSystem>());
    registry->RemoveSystem<WorldEncounterSystem>(registry->GetSystem<WorldEncounterSystem>());

    assetStore->ClearAssets();
}

void SceneTown::Input(std::unique_ptr<EventBus>& eventBus)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
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

void SceneTown::Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt)
{
    // Reset all event handlers for the current frame
    eventBus->Reset();

    registry->GetSystem<CharacterInputSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<InteractSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<WorldCollisionSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<WorldEncounterSystem>().SubscribeToEvents(eventBus);

    // Update the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    registry->GetSystem<CharacterInteractSystem>().Update(eventBus);
    registry->GetSystem<CharacterMovementSystem>().Update(dt, eventBus, mapWidth, mapHeight, registry->GetSystem<RenderTileSystem>().GetSystemEntities());
    registry->GetSystem<CameraMovementSystem>().Update(Engine::Camera(), mapWidth, mapHeight);

    registry->GetSystem<CharacterAnimationSystem>().Update(dt);
    
    registry->GetSystem<CharacterInputSystem>().Update(dt);
}

void SceneTown::Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render 
    registry->GetSystem<RenderTileSystem>().Update(renderer, assetStore, Engine::Camera());
    registry->GetSystem<RenderCharacterSystem>().Update(renderer, assetStore, Engine::Camera());
}