#pragma once

#include "Scene.h"

class SceneTest : public Scene
{
public:
	SceneTest();
	~SceneTest();

	void Setup(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	void Input(std::unique_ptr<EventBus>& eventBus);
	void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventBus>& eventBus, const float dt);
	void Render(std::unique_ptr<Registry>& registry, std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer);

	SDL_Rect GetTileSourceRect(int tileType);
};