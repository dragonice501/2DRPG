#pragma once

#include "Scene.h"
#include "../Objects/Character.h"
#include "../Objects/Components.h"

#include "../Managers/SceneManager.h"

#include "../Utils/Utils.h"

#include <SDL_image.h>
#include <vector>

class SceneOverworld : public Scene
{
public:
	SceneOverworld();
	~SceneOverworld();

	void Setup(SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(SDL_Renderer* renderer, SDL_Rect& camera) override;

private:
	std::vector<Tile> mTiles;
	SDL_Texture* mSpriteSheet;

	std::vector<SceneEntrance> mSceneEntrances;

	Character mSigurd;
};