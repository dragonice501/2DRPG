#pragma once

#include "Actor.h"

class ActorInteractable : public Actor
{
public:
	void Render(SDL_Renderer* renderer) override
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