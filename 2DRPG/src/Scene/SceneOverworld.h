#pragma once

#include "Scene.h"

class SceneOverworld : public Scene
{
public:
	SceneOverworld();
	~SceneOverworld();

	void Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);
	void Shutdown(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	void Input(std::unique_ptr<EventBus>& eventBus);
	void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt);
	void Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);
};