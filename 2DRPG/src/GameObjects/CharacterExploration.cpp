#include "CharacterExploration.h"

#include "../Managers/SceneManager.h"
#include "../Utils/Constants.h"

CharacterExploration::CharacterExploration()
{
}

CharacterExploration::~CharacterExploration()
{
	
}

void CharacterExploration::Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation)
{
}

void CharacterExploration::LoadAnimations(std::string animationsFileName)
{
    Animation newAnimation;
    std::string animationName;

    std::string filePath = "./assets/Files/" + animationsFileName + "Animations.txt";
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

    mCurrentAnimation = "IdleDown";
    mSprite = { 0, 0, 32, 32, 0, -16 };
}

void CharacterExploration::Setup(const int partyIndex, const Vec2& spawnPosition, const Vec2& spawnDirection, const std::string& startingAnimation)
{
    std::string name;
    switch (PlayerManager::GetCharacterAttributes()[partyIndex].characterClass)
    {
        case DANCER:
        {
            name = "Dancer";
            break;
        }
        case KNIGHT:
        {
            name = "Knight";
            break;
        }
        case MAGE:
        {
            name = "Mage";
            break;
        }
        case PALADIN:
        {
            name = "Paladin";
            break;
        }
    }

    mAssetID = name;
    LoadAnimations(name);
    SetPosition(spawnPosition);

    if (GameManager::GetReturnToOverworld())
        mRigidbody.lastVelocity = GameManager::GetPreviousCharacterDirection(partyIndex);
    else
        mRigidbody.lastVelocity = spawnDirection;

    mPartyIndex = partyIndex;
}

void CharacterExploration::Input()
{
    
}

void CharacterExploration::Update(const float dt)
{
    UpdateAnimation();
}

void CharacterExploration::Render()
{
    SDL_Rect destRect =
    {
        mPosition.x * TILE_SPRITE_SCALE + mSprite.positionOffset.x * TILE_SPRITE_SCALE - GraphicsManager::GetCamera().x,
        mPosition.y * TILE_SPRITE_SCALE + mSprite.positionOffset.y * TILE_SPRITE_SCALE - GraphicsManager::GetCamera().y,
        mSprite.srcRect.w * TILE_SPRITE_SCALE,
        mSprite.srcRect.h * TILE_SPRITE_SCALE
    };

    GraphicsManager::DrawSpriteRect(AssetManager::GetAsset(mAssetID), mSprite.srcRect, destRect);
}

void CharacterExploration::CheckInput(const int mapWidth, const int mapHeight, const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters)
{
    
}

void CharacterExploration::UpdateMovement(
    const int mapWidth, const int mapHeight, 
    const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters, const std::vector<Npc>& actors,
    const float dt)
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
                GameManager::SetCurrentCharacterPosition(mPartyIndex, mPosition);

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
                    Vec2 desiredPosition = GetDesiredPosition(characters);
                    if (
                        MovementInsideMap(desiredPosition, mapWidth, mapHeight) &&
                        CanMove(desiredPosition, mapWidth, mapHeight, tiles, characters, actors))
                    {
                        SetMovement(characters);
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
            Vec2 desiredPosition = GetDesiredPosition(characters);
            if (
                MovementInsideMap(desiredPosition, mapWidth, mapHeight) &&
                CanMove(desiredPosition, mapWidth, mapHeight, tiles, characters, actors))
            {
                mMovementState = MS_MOVING;
                SetMovement(characters);
            }
            else
            {
                mMovementState = MS_IDLE;

                if (mPartyIndex == 0)
                {
                    if (InputManager::UpHeld()) mRigidbody.lastVelocity = Vec2(0.0f, -16.0f);
                    else if (InputManager::DownHeld()) mRigidbody.lastVelocity = Vec2(0.0f, 16.0f);
                    else if (InputManager::LeftHeld()) mRigidbody.lastVelocity = Vec2(-16.0f, 0.0f);
                    else if (InputManager::RightHeld()) mRigidbody.lastVelocity = Vec2(16.0f, 0.0f);
                }
            }
        }
    }
}

bool CharacterExploration::MovementPressed()
{
    return mMovement.upHeld || mMovement.downHeld || mMovement.rightHeld || mMovement.leftHeld;
}

Vec2 CharacterExploration::GetDesiredPosition(const std::vector<CharacterExploration>& characters)
{
    Vec2 desiredPosition;

    if (mPartyIndex == 0)
    {
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
    }
    else
    {
        desiredPosition = characters[mPartyIndex - 1].GetPosition();
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

bool CharacterExploration::CanMove(
    const Vec2& desiredPosition, int width, int height,
    const std::vector<Tile>& tiles, const std::vector<CharacterExploration>& characters, const std::vector<Npc>& actors)
{
    int x = desiredPosition.x / TILE_SIZE;
    int y = desiredPosition.y / TILE_SIZE;

    if (mPartyIndex != 0)
    {
        if (mPosition == characters[mPartyIndex - 1].GetPosition() || characters[0].mMovementState == MS_IDLE)
        {
            return false;
        }
    }
    else
    {
        for (Npc actor : actors)
        {
            if (actor.GetPosition() == desiredPosition)
            {
                return false;
            }
        }
    }

    if (GameManager::GetIsOverworld())
    {
        ETerrainType terrain = tiles[x + y * width].TerrainTileType();

        if (terrain == CLIFF) return false;
        else if (terrain == RIVER) return false;
        else if (terrain == MOUNTAIN) return false;
    }
    else if(GameManager::GetIsTown())
    {
        ETownTileType townTile = tiles[x + y * width].TownTileType();

        if (townTile == UNWALKABLE) return false;
    }
    else if (GameManager::GetIsIndoors())
    {
        EIndoorsTileType indoorsTile = tiles[x + y * width].IndoorsTileType();

        if (indoorsTile == ITT_UNWALKABLE) return false;
    }

    return true;
}

void CharacterExploration::SetMovement(const std::vector<CharacterExploration>& characters)
{
    if (mPartyIndex == 0)
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
    else
    {
        Vec2 targetPosition = characters[mPartyIndex - 1].GetPosition();

        mRigidbody.velocity = targetPosition - mPosition;
        mMovement.start = mPosition;
        mMovement.destination = mPosition + mRigidbody.velocity;
    }
}

void CharacterExploration::ResetMovement()
{
    mMovementState = MS_IDLE;
    mMovement.upHeld = false;
    mMovement.downHeld = false;
    mMovement.leftHeld = false;
    mMovement.rightHeld = false;
}

void CharacterExploration::UpdateAnimation()
{
    Animation& anim = mAnimations[mCurrentAnimation];
    anim.currentFrame = ((SDL_GetTicks() - anim.startTime) * anim.frameRateSpeed / 1000) % anim.numFrames;

    mSprite.srcRect.x = anim.frames[anim.currentFrame].position.x;
    mSprite.srcRect.y = anim.frames[anim.currentFrame].position.y;
    mSprite.srcRect.w = anim.frames[anim.currentFrame].width;
    mSprite.srcRect.h = anim.frames[anim.currentFrame].height;

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