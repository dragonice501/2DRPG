#pragma once

#include "SceneExploration.h"

#include "../Managers/SceneManager.h"

class SceneTown : public SceneExploration
{
public:
	SceneTown() : SceneTown("Town") {}
	SceneTown(std::string fileName)
	{
		mFileName = fileName;
	}
	~SceneTown();

	void Setup(SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(SDL_Renderer* renderer, SDL_Rect& camera) override;

	Character mSigurd;
	Actor mDancer;
};