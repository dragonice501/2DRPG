#pragma once

#include "Scene.h"

#include "../Graphics/Font.h"

#include "../Managers/AssetManager.h"

#include "../Objects/Actor.h"
#include "../Objects/ActorNpc.h"
#include "../Objects/ActorInteractable.h"
#include "../Objects/CharacterExploration.h"
#include "../Objects/Components.h"
#include "../Objects/EnemyEncounter.h"

#include "../UI/UIButton.h"
#include "../UI/MenuParty.h"
#include "../UI/MenuInteract.h"

#include "../Utils/Utils.h"

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
	std::vector<Tile> mTiles;
	std::string mTileMapName;

	std::string mBattleIconsFilePath = "MenuIcons";
	std::map<std::string, Sprite> mBattleIconsMap;

	std::vector<SceneEntrance> mSceneEntrances;
	std::vector<ActorNpc> mNpcs;
	std::vector<ActorInteractable> mInteractables;
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

	ActorNpc* mInteractedActor = nullptr;

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