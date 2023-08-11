#pragma once

#include "Scene.h"
#include "../ECS/ECS.h"

class ScenePikuma : public Scene
{
public:
	ScenePikuma();
	~ScenePikuma();

	void Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) override;

	void Input(std::unique_ptr<EventBus>& eventBus) override;
	void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt) override;
	void Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) override;
};