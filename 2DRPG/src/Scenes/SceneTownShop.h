#pragma once

#include "SceneExploration.h"

class SceneTownShop : public SceneExploration
{
public:
	SceneTownShop() : SceneTownShop("TownShop") {}
	SceneTownShop(std::string fileName)
	{
		mFileName = fileName;
	}
	~SceneTownShop();

	void Setup(static SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(static SDL_Renderer* renderer, static SDL_Rect& camera) override;
};