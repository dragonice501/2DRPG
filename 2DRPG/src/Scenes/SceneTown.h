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
	void Render(static SDL_Renderer* renderer, static SDL_Rect& camera) override;

	ECharacterState mCharacterState = CS_MOVING;
	CharacterExploration mSigurd;
	Actor* mInteractedActor = nullptr;
	std::vector<CharacterExploration> mCharacters;

	int mInteractMenuIndex = 0;
	int mInteractMenuOptions = 2;
};