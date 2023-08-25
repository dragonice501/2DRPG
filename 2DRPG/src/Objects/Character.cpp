#include "Character.h"

#include "../Managers/SceneManager.h"
#include "../Utils/Constants.h"

Character::Character()
{
}

Character::~Character()
{
	SDL_DestroyTexture(mSpriteSheet);
}

void Character::Init(const std::string& spriteSheetPath, const std::string& animationsFilePath, const Vec2& spawnPosition, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(spriteSheetPath.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }

    position = spawnPosition;
    mSprite = { 32, 32, 0, -16, 0, 64 };

    LoadAnimations(animationsFilePath);
    mCurrentAnimation = "IdleRight";
}

void Character::LoadAnimations(std::string animationsFilePath)
{
    Animation newAnimation;
    std::string animationName;

    std::string filePath = "./assets/" + animationsFilePath + ".txt";
    std::ifstream file(filePath);
    std::string type;
    while (file >> type)
    {
        if (type == "Animation")
        {
            int animationFrames, animationFrameRate;
            bool shouldLoop;

            file >> animationName >> animationFrames >> animationFrameRate >> shouldLoop;

            newAnimation = { animationFrames, animationFrameRate, shouldLoop };

            mAnimations.emplace(animationName, newAnimation);
        }
        else if (type == "Frame")
        {
            int frameX, frameY, frameWidth, frameHeight;

            file >> frameX >> frameY >> frameWidth >> frameHeight;

            AnimationFrame newFrame = { Vec2(frameX, frameY), frameWidth, frameHeight };

            mAnimations[animationName].frames.push_back(newFrame);
        }
    }
}

void Character::Update(const float dt)
{
    UpdateAnimation();
}

void Character::Render(SDL_Renderer* renderer)
{
    SDL_Rect destRect =
    {
        position.x * TILE_SPRITE_SCALE + mSprite.xOffset * TILE_SPRITE_SCALE - Engine::Camera().x,
        position.y * TILE_SPRITE_SCALE + mSprite.yOffset * TILE_SPRITE_SCALE - Engine::Camera().y,
        mSprite.width * TILE_SPRITE_SCALE,
        mSprite.height * TILE_SPRITE_SCALE
    };

    SDL_RenderCopy(renderer, mSpriteSheet, &mSprite.srcRect, &destRect);
}

void Character::UpdateMovement(const int mapWidth, const int mapHeight, const std::vector<Tile>& mTiles, const float dt)
{
    mMovement.stepTaken = false;

    if (mMovementState == MS_MOVING)
    {
        if (position != mMovement.destination)
        {
            mMovement.rate += 2 * dt;
            position = Vec2::Lerp(mMovement.start, mMovement.destination, mMovement.rate);
            if (position == mMovement.destination)
            {
                mMovement.rate = 0.0f;
                mMovement.start = position;
                mMovement.destination = Vec2(0.0f);
                mMovement.stepTaken = true;
                mRigidbody.lastVelocity = mRigidbody.velocity;
                mRigidbody.velocity = Vec2(0.0f);
                mSprite.srcRect.y = 0;

                int index = position.x / TILE_SIZE + (position.y / TILE_SIZE) * mapWidth;

                if (MovementPressed())
                {
                    Vec2 desiredPosition = GetDesiredPosition();
                    if (
                        MovementInsideMap(desiredPosition, mapWidth, mapHeight) &&
                        CanMove(desiredPosition, mapWidth, mapHeight, mTiles))
                    {
                        SetMovement();
                    }
                    else
                    {
                        mMovementState = MS_IDLE;
                    }
                }
                else
                {
                    mMovementState = MS_IDLE;
                }
            }
        }
    }
    else
    {
        if (MovementPressed())
        {
            Vec2 desiredPosition = GetDesiredPosition();
            if (MovementInsideMap(desiredPosition, mapWidth, mapHeight))
            {
                if(CanMove(desiredPosition, mapWidth, mapHeight, mTiles))
                {
                    mMovementState = MS_MOVING;
                    SetMovement();
                }
            }
            else
            {
                mMovementState = MS_IDLE;

                if (mInput.upPressed) mRigidbody.lastVelocity = Vec2(0.0f, -1.0f);
                else if (mInput.downPressed) mRigidbody.lastVelocity = Vec2(0.0f, 1.0f);
                else if (mInput.leftPressed) mRigidbody.lastVelocity = Vec2(-1.0f, 0.0f);
                else if (mInput.rightPressed) mRigidbody.lastVelocity = Vec2(1.0f, 0.0f);
            }
        }
    }
}

bool Character::MovementPressed()
{
    return mInput.upPressed || mInput.downPressed || mInput.leftPressed || mInput.rightPressed;
}

Vec2 Character::GetDesiredPosition()
{
    Vec2 desiredPosition;

    if (mInput.upPressed)
    {
        desiredPosition = Vec2(static_cast<int>(position.x), static_cast<int>(position.y - TILE_SIZE));
    }
    else if (mInput.downPressed)
    {
        desiredPosition = Vec2(static_cast<int>(position.x), static_cast<int>(position.y + TILE_SIZE));
    }
    else if (mInput.leftPressed)
    {
        desiredPosition = Vec2(static_cast<int>(position.x - TILE_SIZE), static_cast<int>(position.y));
    }
    else if (mInput.rightPressed)
    {
        desiredPosition = Vec2(static_cast<int>(position.x + TILE_SIZE), static_cast<int>(position.y));
    }

    return desiredPosition;
}

bool Character::MovementInsideMap(const Vec2& position, const int width, const int height)
{
    return !(
        position.x < 0 ||
        position.x + TILE_SIZE > width * TILE_SIZE ||
        position.y < 0 ||
        position.y + TILE_SIZE > height * TILE_SIZE);
}

bool Character::CanMove(const Vec2& desiredPosition, int width, int height, const std::vector<Tile>& mTiles)
{
    int x = desiredPosition.x / TILE_SIZE;
    int y = desiredPosition.y / TILE_SIZE;

    if (SceneManager::Instance().GetIsOverworld())
    {
        ETerrainType terrain = mTiles[x + y * width].terrainType;

        if (terrain == CLIFF) return false;
        else if (terrain == RIVER) return false;
        else if (terrain == MOUNTAIN) return false;
    }
    else
    {
        ETownTileType townTile = mTiles[x + y * width].townType;

        if (townTile == UNWALKABLE) return false;
    }

    return true;
}

void Character::SetMovement()
{
    if (mInput.upPressed)
    {
        mRigidbody.velocity = Vec2(0.0f, -TILE_SIZE);
        mMovement.start = position;
        mMovement.destination = position + mRigidbody.velocity;
    }
    else if (mInput.downPressed)
    {
        mRigidbody.velocity = Vec2(0.0f, TILE_SIZE);
        mMovement.start = position;
        mMovement.destination = position + mRigidbody.velocity;
    }
    else if (mInput.leftPressed)
    {
        mRigidbody.velocity = Vec2(-TILE_SIZE, 0.0f);
        mMovement.start = position;
        mMovement.destination = position + mRigidbody.velocity;
    }
    else if (mInput.rightPressed)
    {
        mRigidbody.velocity = Vec2(TILE_SIZE, 0.0f);
        mMovement.start = position;
        mMovement.destination = position + mRigidbody.velocity;
    }
}

void Character::UpdateAnimation()
{
    if (mMovementState == MS_MOVING)
    {
        if (mRigidbody.velocity.y < 0)
        {
            mCurrentAnimation = "MovingUp";
        }
        else if (mRigidbody.velocity.y > 0)
        {
            mCurrentAnimation = "MovingDown";
        }
        else if (mRigidbody.velocity.x < 0)
        {
            mCurrentAnimation = "MovingLeft";
        }
        else if (mRigidbody.velocity.x > 0)
        {
            mCurrentAnimation = "MovingRight";
        }
    }
    else if (mMovementState == MS_IDLE)
    {
        if (mRigidbody.lastVelocity.y < 0)
        {
            mCurrentAnimation = "IdleUp";
        }
        else if (mRigidbody.lastVelocity.y > 0)
        {
            mCurrentAnimation = "IdleDown";
        }
        else if (mRigidbody.lastVelocity.x < 0)
        {
            mCurrentAnimation = "IdleLeft";
        }
        else if (mRigidbody.lastVelocity.x > 0)
        {
            mCurrentAnimation = "IdleRight";
        }
    }

    Animation& anim = mAnimations[mCurrentAnimation];
    anim.currentFrame = ((SDL_GetTicks() - anim.startTime) * anim.frameRateSpeed / 1000) % anim.numFrames;

    mSprite.srcRect.x = anim.frames[anim.currentFrame].position.x;
    mSprite.srcRect.y = anim.frames[anim.currentFrame].position.y;
    mSprite.srcRect.w = anim.frames[anim.currentFrame].width;
    mSprite.srcRect.h = anim.frames[anim.currentFrame].height;
}