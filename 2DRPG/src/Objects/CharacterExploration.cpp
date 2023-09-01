#include "CharacterExploration.h"

#include "../Managers/SceneManager.h"
#include "../Utils/Constants.h"

CharacterExploration::CharacterExploration()
{
}

CharacterExploration::~CharacterExploration()
{
	SDL_DestroyTexture(mSpriteSheet);
}

void CharacterExploration::Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation)
{
    Actor::Init(name, spawnPosition, renderer);

    mPosition = spawnPosition;
}

void CharacterExploration::LoadAnimations(std::string animationsFileName)
{
    Actor::LoadAnimations(animationsFileName);
}

void CharacterExploration::Update(const float dt)
{
    CheckInteracting();

    Actor::UpdateAnimation();
    UpdateAnimation();
}

void CharacterExploration::Render(SDL_Renderer* renderer)
{
    Actor::Render(renderer);
}

void CharacterExploration::CheckInteracting()
{
    
}

void CharacterExploration::UpdateMovement(const int mapWidth, const int mapHeight, const std::vector<Tile>& tiles, const std::vector<Actor>& actors, const float dt)
{
    mMovement.stepTaken = false;

    if (mMovementState == MS_MOVING)
    {
        if (mPosition != mMovement.destination)
        {
            mMovement.rate += 2 * dt;
            mPosition = Vec2::Lerp(mMovement.start, mMovement.destination, mMovement.rate);
            if (mPosition == mMovement.destination)
            {
                mMovement.rate = 0.0f;
                mMovement.start = mPosition;
                mMovement.destination = Vec2(0.0f);
                mMovement.stepTaken = true;
                mRigidbody.lastVelocity = mRigidbody.velocity;
                mRigidbody.velocity = Vec2(0.0f);
                mSprite.srcRect.y = 0;

                int index = mPosition.x / TILE_SIZE + (mPosition.y / TILE_SIZE) * mapWidth;

                if (MovementPressed())
                {
                    Vec2 desiredPosition = GetDesiredPosition();
                    if (MovementInsideMap(desiredPosition, mapWidth, mapHeight) && CanMove(desiredPosition, mapWidth, mapHeight, tiles, actors))
                    {
                        SetMovement();
                    }
                    else
                    {
                        mMovementState = MS_IDLE;
                        mRigidbody.lastVelocity = desiredPosition - mPosition;
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
            if (MovementInsideMap(desiredPosition, mapWidth, mapHeight) && CanMove(desiredPosition, mapWidth, mapHeight, tiles, actors))
            {
                mMovementState = MS_MOVING;
                SetMovement();
            }
            else
            {
                mMovementState = MS_IDLE;

                if (InputManager::UpHeld()) mRigidbody.lastVelocity = Vec2(0.0f, -16.0f);
                else if (InputManager::DownHeld()) mRigidbody.lastVelocity = Vec2(0.0f, 16.0f);
                else if (InputManager::LeftHeld()) mRigidbody.lastVelocity = Vec2(-16.0f, 0.0f);
                else if (InputManager::RightHeld()) mRigidbody.lastVelocity = Vec2(16.0f, 0.0f);
            }
        }
    }
}

bool CharacterExploration::MovementPressed()
{
    return InputManager::UpHeld() || InputManager::DownHeld() || InputManager::LeftHeld() || InputManager::RightHeld();
}

Vec2 CharacterExploration::GetDesiredPosition()
{
    Vec2 desiredPosition;

    if (InputManager::UpHeld())
    {
        desiredPosition = Vec2(static_cast<int>(mPosition.x), static_cast<int>(mPosition.y - TILE_SIZE));
    }
    else if (InputManager::DownHeld())
    {
        desiredPosition = Vec2(static_cast<int>(mPosition.x), static_cast<int>(mPosition.y + TILE_SIZE));
    }
    else if (InputManager::LeftHeld())
    {
        desiredPosition = Vec2(static_cast<int>(mPosition.x - TILE_SIZE), static_cast<int>(mPosition.y));
    }
    else if (InputManager::RightHeld())
    {
        desiredPosition = Vec2(static_cast<int>(mPosition.x + TILE_SIZE), static_cast<int>(mPosition.y));
    }

    return desiredPosition;
}

bool CharacterExploration::MovementInsideMap(const Vec2& position, const int width, const int height)
{
    return !(
        position.x < 0 ||
        position.x + TILE_SIZE > width * TILE_SIZE ||
        position.y < 0 ||
        position.y + TILE_SIZE > height * TILE_SIZE);
}

bool CharacterExploration::CanMove(const Vec2& desiredPosition, int width, int height, const std::vector<Tile>& tiles, const std::vector<Actor>& actors)
{
    int x = desiredPosition.x / TILE_SIZE;
    int y = desiredPosition.y / TILE_SIZE;

    for (const Actor& actor : actors)
    {
        if (desiredPosition == actor.GetPosition()) return false;
    }

    if (SceneManager::GetIsOverworld())
    {
        ETerrainType terrain = tiles[x + y * width].terrainType;

        if (terrain == CLIFF) return false;
        else if (terrain == RIVER) return false;
        else if (terrain == MOUNTAIN) return false;
    }
    else
    {
        ETownTileType townTile = tiles[x + y * width].townType;

        if (townTile == UNWALKABLE) return false;
    }

    return true;
}

void CharacterExploration::SetMovement()
{
    if (InputManager::UpHeld())
    {
        mRigidbody.velocity = Vec2(0.0f, -TILE_SIZE);
        mMovement.start = mPosition;
        mMovement.destination = mPosition + mRigidbody.velocity;
    }
    else if (InputManager::DownHeld())
    {
        mRigidbody.velocity = Vec2(0.0f, TILE_SIZE);
        mMovement.start = mPosition;
        mMovement.destination = mPosition + mRigidbody.velocity;
    }
    else if (InputManager::LeftHeld())
    {
        mRigidbody.velocity = Vec2(-TILE_SIZE, 0.0f);
        mMovement.start = mPosition;
        mMovement.destination = mPosition + mRigidbody.velocity;
    }
    else if (InputManager::RightHeld())
    {
        mRigidbody.velocity = Vec2(TILE_SIZE, 0.0f);
        mMovement.start = mPosition;
        mMovement.destination = mPosition + mRigidbody.velocity;
    }
}

void CharacterExploration::UpdateAnimation()
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
}