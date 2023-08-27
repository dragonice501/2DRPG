#include "Utils.h"

#include <iostream>

float Clampf(const float v, const float min, const float max)
{
	if (v < min) return min;
	else if (v > max) return max;
	else return v;
}

ETownTileType GetTownTileType(const int mapSpriteIndex)
{
	for (const int index : mWalkableIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return WALKABLE;
		}
	}

	return UNWALKABLE;
}

ETerrainType GetTerrainType(const int mapSpriteIndex)
{
	for (const int index : mChurchIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return CHURCH;
		}
	}

	for (const int index : mVillageIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return VILLAGE;
		}
	}

	for (const int index : mBragiTowerIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return BRAGI_TOWER;
		}
	}

	for (const int index : mCastleDefenseIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return CASTLE_DEFENSE;
		}
	}

	for (const int index : mBridgeIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return BRIDGE;
		}
	}

	for (const int index : mSeaIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return SEA;
		}
	}

	for (const int index : mForestIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return FOREST;
		}
	}

	for (const int index : mRiverIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return RIVER;
		}
	}

	for (const int index : mSandIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return SAND;
		}
	}

	for (const int index : mThicketIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return THICKET;
		}
	}

	for (const int index : mCastleWallIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return CASTLE_WALL;
		}
	}

	for (const int index : mCliffIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return CLIFF;
		}
	}

	for (const int index : mPlainIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return PLAIN;
		}
	}

	for (const int index : mRoadIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return ROAD;
		}
	}

	for (const int index : mMountainIndeces)
	{
		if (mapSpriteIndex == index)
		{
			return MOUNTAIN;
		}
	}

	return UNDEFINED;
}

void PrintTerrainType(const ETerrainType terrain)
{
	switch (terrain)
	{
		case BRAGI_TOWER: std::cout << "BRAGI_TOWER" << std::endl; break;
		case BRIDGE: std::cout << "BRIDGE" << std::endl; break;
		case CASTLE_DEFENSE: std::cout << "CASTLE_DEFENSE" << std::endl; break;
		case CASTLE_WALL: std::cout << "CASTLE_WALL" << std::endl; break;
		case DESERT: std::cout << "DESERT" << std::endl; break;
		case CHURCH: std::cout << "CHURCH" << std::endl; break;
		case CLIFF: std::cout << "CLIFF" << std::endl; break;
		case FOREST: std::cout << "FOREST" << std::endl; break;
		case MOUNTAIN: std::cout << "MOUNTAIN" << std::endl; break;
		case PEAK: std::cout << "PEAK" << std::endl; break;
		case PLAIN: std::cout << "PLAIN" << std::endl; break;
		case RIVER: std::cout << "RIVER" << std::endl; break;
		case ROAD: std::cout << "ROAD" << std::endl; break;
		case RUINS: std::cout << "RUINS" << std::endl; break;
		case SAND: std::cout << "SAND" << std::endl; break;
		case SEA: std::cout << "SEA" << std::endl; break;
		case THICKET: std::cout << "THICKET" << std::endl; break;
		case VILLAGE: std::cout << "VILLAGE" << std::endl; break;
		case UNDEFINED: std::cout << "UNDEFINED" << std::endl; break;
	}
}

void ConvertDialogueDashes(std::string& string)
{
	for (char& c : string)
	{
		if (c == '-') c = ' ';
	}
}