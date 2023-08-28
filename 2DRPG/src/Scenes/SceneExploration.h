#pragma once

#include "Scene.h"
#include "../Objects/Actor.h"
#include "../Objects/Character.h"
#include "../Objects/Components.h"

#include "../Utils/Utils.h"

#include <SDL_image.h>
#include <vector>

class SceneExploration : public Scene
{
public:
	SceneExploration();
	~SceneExploration();

	virtual void Setup(static SDL_Renderer* renderer);
	virtual void Shutdown() override;

	virtual void Input() override;
	virtual void Update(const float dt) override;
	virtual void Render(static SDL_Renderer* renderer, static SDL_Rect& camera) override;

	std::string mFileName;

protected:
	std::vector<Tile> mTiles;
	SDL_Texture* mSpriteSheet;

	std::vector<SceneEntrance> mSceneEntrances;
	std::vector<Actor> mActors;
	std::vector<Character> mCharacters;

	Vec2 spawnPosition;
};