#pragma once

#include "GameObject.h"

#include "Components.h"

#include "Utils.h"

class Tile : public GameObject
{
public:
	Tile(const Vec2& position, const size_t spriteIndex)
	{
		this->transform = { position.x, position.y };
		this->spriteIndex = spriteIndex;

		terrainType = GetTerrainType(spriteIndex);
		townType = GetTownTileType(spriteIndex);
		indoorsType = GetIndoorsTileType(spriteIndex);
	}

	const TransformComponent& GetTransformComponent() const { return transform; }
	const size_t GetSpriteIndex() const { return spriteIndex; }

	const ETerrainType TerrainTileType() const { return terrainType; }
	const ETownTileType TownTileType() const { return townType; }
	const EIndoorsTileType IndoorsTileType() const { return indoorsType; }

	void Input() override;
	void Update(float dt) override;
	void Render() override;

private:
	TransformComponent transform;
	
	size_t spriteIndex;

	ETerrainType terrainType;
	ETownTileType townType;
	EIndoorsTileType indoorsType;
};