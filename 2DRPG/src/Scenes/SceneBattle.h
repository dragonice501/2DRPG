#pragma once

#include "Scene.h"
#include "../Utils/Utils.h"
#include "../Objects/Enemy.h"
#include "../Objects/EnemyEncounter.h"
#include "../Objects/CharacterBattle.h"

#include "../Graphics/Font.h"

#include "../Managers/SceneManager.h"
#include "../Managers/PlayerManager.h"

#include <SDL.h>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <time.h>

class SceneBattle : public Scene
{
public:
	SceneBattle() : SceneBattle(PLAIN, std::vector<EnemyEncounter>()) {}
	SceneBattle(ETerrainType terrain, const std::vector<EnemyEncounter> enemyEncounters);

	void Setup(static SDL_Renderer* renderer);
	void Shutdown();

	void Input();
	void Update(const float dt);
	void Render(static SDL_Renderer* renderer, static SDL_Rect& camera);

private:
	SDL_Texture* mBackgroundTexture = nullptr;
	std::string mBackgroundImageFilePath;

	std::vector<CharacterBattle> mPlayerCharacters;

	SDL_Texture* mEnemiesTexture = nullptr;
	std::map<std::string, Enemy> mEnemyMap;
	std::vector<Enemy> mEnemies;

	std::vector<EnemyEncounter> mEnemyEncounters;

	int mBattleMenuIndex = 0;
	int mBattleMenuIndexOptions = 4;

	std::vector<Vec2> mPlayerCharacterPositions =
	{
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE),
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE) + Vec2(16.0f, 16.0f) * TILE_SPRITE_SCALE,
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE) + Vec2(32.0f, 32.0f) * TILE_SPRITE_SCALE,
		Vec2(GraphicsManager::WindowWidth() - 96 * TILE_SPRITE_SCALE, 24 * TILE_SPRITE_SCALE) + Vec2(48.0f, 48.0f) * TILE_SPRITE_SCALE
	};

	std::vector<Vec2> mSmallEnemyPositions =
	{
		Vec2(0.0f, 0.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(0.0f, 1.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(0.0f, 2.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(1.0f, 0.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(1.0f, 1.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
		Vec2(1.0f, 2.0f) * TILE_SPRITE_SCALE * 32 + 32 * TILE_SPRITE_SCALE,
	};
};