#pragma once

#include "Scene.h"
#include "../Utils/Utils.h"

#include "../Managers/SceneManager.h"

#include <SDL.h>
#include <string>

class SceneBattle : public Scene
{
public:
	SceneBattle() : SceneBattle(PLAIN) {}
	SceneBattle(ETerrainType terrain);

	void Setup(static SDL_Renderer* renderer);
	void Shutdown();

	void Input();
	void Update(const float dt);
	void Render(static SDL_Renderer* renderer, static SDL_Rect& camera);

private:
	SDL_Texture* mBackgroundTexture = nullptr;
	std::string mBackgroundImageFilePath;

	int mBattleMenuIndex = 0;
	int mBattleMenuIndexOptions = 4;
};