#include "Utils.h"

#include <iostream>

float Clampf(const float v, const float min, const float max)
{
	if (v < min) return min;
	else if (v > max) return max;
	else return v;
}

ETerrainType GetTerrainType(const int mapSpriteIndex)
{
	for (const int index : mSeaIndeces)
	{
		if (mapSpriteIndex == index)
		{
			//std::cout << "SEA" << std::endl;
			return SEA;
		}
	}

	for (const int index : mRiverIndeces)
	{
		if (mapSpriteIndex == index)
		{
			std::cout << "RIVER" << std::endl;
			return RIVER;
		}
	}

	for (const int index : mRoadIndeces)
	{
		if (mapSpriteIndex == index)
		{
			std::cout << "ROAD" << std::endl;
			return ROAD;
		}
	}

	for (const int index : mPlainIndeces)
	{
		if (mapSpriteIndex == index)
		{
			std::cout << "PLAIN" << std::endl;
			return PLAIN;
		}
	}

	for (const int index : mForestIndeces)
	{
		if (mapSpriteIndex == index)
		{
			std::cout << "FOREST" << std::endl;
			return FOREST;
		}
	}

	for (const int index : mMountainIndeces)
	{
		if (mapSpriteIndex == index)
		{
			std::cout << "MOUNTAIN" << std::endl;
			return MOUNTAIN;
		}
	}

	for (const int index : mVillageIndeces)
	{
		if (mapSpriteIndex == index)
		{
			std::cout << "VILLAGE" << std::endl;
			return VILLAGE;
		}
	}

	for (const int index : mCastleDefenseIndeces)
	{
		if (mapSpriteIndex == index)
		{
			//std::cout << "CASTLE_DEFENSE" << std::endl;
			return CASTLE_DEFENSE;
		}
	}

	return UNDEFINED;
}