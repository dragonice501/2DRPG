#pragma once

#include "Scene.h"

#include "Components.h"

#include "Interactable.h"
#include "Npc.h"
#include "CharacterExploration.h"
#include "EnemyEncounter.h"
#include "Tile.h"

#include "Font.h"

#include "AssetManager.h"

#include "UIButton.h"
#include "MenuParty.h"
#include "MenuInteract.h"

#include "Utils.h"

#include <SDL_image.h>
#include <vector>

class SceneExploration : public Scene
{
public:
	SceneExploration();
	~SceneExploration();

	inline const int GetMapWidth() const { return mMapWidth; }
	inline const int GetMapHeight() const { return mMapHeight; }

	virtual void Setup(static SDL_Renderer* renderer);
	virtual void Shutdown() override;

	virtual void Input() override;
	virtual void Update(const float dt) override;
	virtual void Render(static SDL_Rect& camera) override;

	virtual void DrawCursor();

	void ExitMenu() override { mExplorationState = ES_EXPLORING; }

	void SetupCharacters();

	void AskAboutKeyword(int index);
	void ClearInteractedActor() { mInteractedActor = nullptr; }
	void SwapCharacters(int first, int second);

	std::string mFileName;

protected:
	bool mDrawMapCentered = false;

	std::vector<Tile> mTiles;
	std::string mTileMapName;

	std::map<std::string, SpriteComponent> mBattleIconsMap;

	std::vector<SceneEntrance> mSceneEntrances;
	std::vector<Interactable> mInteractables;
	std::vector<Npc> mNpcs;
	std::vector<CharacterExploration> mCharacters;
	std::vector<EnemyEncounter> mEnemyEncounters;

	Vec2 mSpawnPosition;
	std::vector<Vec2> mSpawnPositions;
	std::vector<Vec2> mSpawnDirections;

	EExplorationState mExplorationState = ES_EXPLORING;
	int mPartyMenuIndex = 0;
	int mPartyMenuIndexOptions = 7;

	ECharacterState mCharacterState = CS_MOVING;
	
	int mInteractMenuIndex = 0;
	int mInteractMenuOptions = 3;

	int mAskingMenuIndex = 0;

	UIButton mButton;
	MenuParty mPartyMenu;
	MenuInteract mInteractMenu;

	Npc* mInteractedActor = nullptr;

	int mEncounterStepsMin = 10;
	int mEncounterStepsMax = 99;
	int mStepsUntilEncounter = 10;

	Vec2 mCharacterUIPositions[4] =
	{
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.2f),
		Vec2(1.0f, 1.2f)
	};
};