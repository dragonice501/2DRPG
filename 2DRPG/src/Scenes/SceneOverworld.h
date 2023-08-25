#pragma once

#include "SceneExploration.h"

#include "../Managers/SceneManager.h"

class SceneOverworld : public SceneExploration
{
public:
	SceneOverworld() : SceneOverworld("World") {}
	SceneOverworld(std::string fileName)
	{
		mFileName = fileName;
	}
	~SceneOverworld();

	void Setup(SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(SDL_Renderer* renderer, SDL_Rect& camera) override;

	Character mSigurd;
};