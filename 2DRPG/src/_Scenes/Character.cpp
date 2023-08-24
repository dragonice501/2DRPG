#include "Character.h"

#include "../Utils/Constants.h"

Character::Character()
{
}

Character::~Character()
{
	SDL_DestroyTexture(mSpriteSheet);
}

void Character::Init(std::string mSpriteSheetPath, SDL_Renderer* renderer)
{
    position = Vec2(16.0f);

    SDL_Surface* surface = IMG_Load(mSpriteSheetPath.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    mSprite = { 32, 32, 0, -16, 0, 64 };
    mIdleAnimation = { 4, 4, true };
}

void Character::Update(const float dt)
{
    if (mInput.upPressed)
    {
        mRigidbody.velocity = Vec2(0.0f, -1.0f);
        mSprite.srcRect.y = mSprite.height * 0;
    }
    else if (mInput.downPressed)
    {
        mRigidbody.velocity = Vec2(0.0f, 1.0f);
        mSprite.srcRect.y = mSprite.height * 1;
    }
    else if (mInput.leftPressed)
    {
        mRigidbody.velocity = Vec2(-1.0f, 0.0f);
        mSprite.srcRect.y = mSprite.height * 2;
    }
    else if (mInput.rightPressed)
    {
        mRigidbody.velocity = Vec2(1.0f, 0.0f);
        mSprite.srcRect.y = mSprite.height * 3;
    }

    mIdleAnimation.currentFrame = ((SDL_GetTicks() - mIdleAnimation.startTime) * mIdleAnimation.frameRateSpeed / 1000) % mIdleAnimation.numFrames;
    mSprite.srcRect.x = mIdleAnimation.currentFrame * mSprite.srcRect.w;
}

void Character::Render(SDL_Renderer* renderer)
{
    SDL_Rect destRect =
    {
        position.x * TILE_SPRITE_SCALE + mSprite.xOffset * TILE_SPRITE_SCALE,
        position.y * TILE_SPRITE_SCALE + mSprite.yOffset * TILE_SPRITE_SCALE,
        mSprite.width * TILE_SPRITE_SCALE,
        mSprite.height * TILE_SPRITE_SCALE
    };

    SDL_RenderCopy(renderer, mSpriteSheet, &mSprite.srcRect, &destRect);
}