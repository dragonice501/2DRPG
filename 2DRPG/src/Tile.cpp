#include "Tile.h"

#include "AssetManager.h"
#include "GraphicsManager.h"

#include <SDL.h>

void Tile::Input()
{
}

void Tile::Update(float dt)
{
}

void Tile::Render()
{
    SDL_Rect& camera = GraphicsManager::GetCamera();

    SDL_Rect srcRect =
    {
        spriteIndex % SPRITE_SHEET_SIZE * TILE_SIZE,
        spriteIndex / SPRITE_SHEET_SIZE * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE
    };

    SDL_Rect destRect =
    {
        transform.x * TILE_SPRITE_SCALE - GraphicsManager::GetCamera().x,
        transform.y * TILE_SPRITE_SCALE - GraphicsManager::GetCamera().y,
        TILE_SIZE * TILE_SPRITE_SCALE,
        TILE_SIZE * TILE_SPRITE_SCALE
    };

    GraphicsManager::DrawSpriteRect(AssetManager::GetTileMapTexture(), srcRect, destRect);
}