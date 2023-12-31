#pragma once

#include "SceneExploration.h"

class SceneOverworld : public SceneExploration
{
public:
	SceneOverworld() : SceneOverworld("World") {}
	SceneOverworld(std::string fileName)
	{
		mFileName = fileName;
	}
	~SceneOverworld();

	void Setup(static SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(static SDL_Rect& camera) override;
};