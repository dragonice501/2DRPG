#pragma once

#include "SceneRef.h"
#include "Character.h"
#include "ComponentsRef.h"

#include "../Utils/Utils.h"

#include <SDL_image.h>
#include <vector>

class SceneRefOverworld : public SceneRef
{
public:
	SceneRefOverworld();
	~SceneRefOverworld();

	void Setup(SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(SDL_Renderer* renderer, SDL_Rect& camera) override;

private:
	std::vector<Tile> mTiles;
	SDL_Texture* mSpriteSheet;

	Character mSigurd;
};