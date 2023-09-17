#pragma once

#include "Scene.h"

#include "../Graphics/Font.h"

#include "../Objects/Actor.h"
#include "../Objects/CharacterExploration.h"
#include "../Objects/Components.h"
#include "../Objects/Enemy.h"
#include "../Objects/EnemyEncounter.h"

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

	virtual void DrawPartyMenu(static SDL_Renderer* renderer);

	void SetupCharacters();

	std::string mFileName;

protected:
	std::vector<Tile> mTiles;
	SDL_Texture* mTileMap;

	std::vector<SceneEntrance> mSceneEntrances;
	std::vector<Actor> mActors;
	std::vector<CharacterExploration> mCharacters;
	std::vector<EnemyEncounter> mEnemyEncounters;

	Vec2 mSpawnPosition;
	std::vector<Vec2> mSpawnPositions;
	std::vector<Vec2> mSpawnDirections;

	EExplorationState mExplorationState = ES_EXPLORING;
	int mPartyMenuIndex = 0;
	int mPartyMenuIndexOptions = 6;

	int mStepsUntilEncounterMax = 5;
	int mStepsUntilEncounter = mStepsUntilEncounterMax;

	Vec2 mCharacterUIPositions[4] =
	{
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.2f),
		Vec2(1.0f, 1.2f)
	};
};