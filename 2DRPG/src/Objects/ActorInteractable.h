#pragma once

#include "Actor.h"

class ActorInteractable : public Actor
{
public:
	void Render() override
	{
		GraphicsManager::DrawFillRect(
			mPosition.x * TILE_SPRITE_SCALE,
			mPosition.y * TILE_SPRITE_SCALE,
			TILE_SIZE * TILE_SPRITE_SCALE,
			TILE_SIZE * TILE_SPRITE_SCALE,
			0xFF000000);
	}

private:

};