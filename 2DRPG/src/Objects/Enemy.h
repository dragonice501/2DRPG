#pragma once

#include "Components.h"

struct Enemy
{
	Enemy(const int xOffset = 0, const int yOffset = 0, const int width = 0, const int height = 0)
	{
		rect = { xOffset, yOffset, width, height };
	}
	size_t battleSpawnPosition;
	SDL_Rect rect;
};