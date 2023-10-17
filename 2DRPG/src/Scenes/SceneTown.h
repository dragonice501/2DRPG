#pragma once

#include "SceneExploration.h"

#include "../Objects/CharacterExploration.h"
#include "../Managers/SceneManager.h"

#include <vector>

class SceneTown : public SceneExploration
{
public:
	SceneTown() : SceneTown("Town") {}
	SceneTown(std::string fileName)
	{
		mFileName = fileName;
	}
	~SceneTown();

	void Setup(static SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(static SDL_Rect& camera) override;
};