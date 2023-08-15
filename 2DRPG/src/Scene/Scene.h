#pragma once

#include "../Engine/Engine.h"

#include "../AssetStore/AssetStore.h"

#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../ECS/Systems.h"

#include "../EventBus/EventBus.h"
#include "../EventBus/Events.h"

#include "../Utils/Constants.h"

#include <SDL.h>
#include <memory>
#include <fstream>

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) = 0;

	virtual void Input(std::unique_ptr<EventBus>& eventBus) = 0;
	virtual void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt) = 0;
	virtual void Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) = 0;

protected:
	int mapWidth = 0;
	int mapHeight = 0;
	int startX = 0;
	int startY = 0;
};