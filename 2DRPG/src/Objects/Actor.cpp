#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
    
}

void Actor::Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation)
{
    std::string filePath = "./assets/" + name + ".png";
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    mPosition = spawnPosition;
    mSprite.positionOffset = { 0.0f, -16.0f };
    LoadAnimations(name);
    mCurrentAnimation = startinAnimation;
}

void Actor::LoadAnimations(std::string animationsFilePath)
{
    Animation newAnimation;
    std::string animationName;

    std::string filePath = "./assets/" + animationsFilePath + "Animations.txt";
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

void Actor::Input()
{
}

void Actor::Update(const float dt)
{
    UpdateAnimation();
}

void Actor::Render(SDL_Renderer* renderer)
{
    /*GraphicsManager::DrawFillRect(
        mPosition.x * TILE_SPRITE_SCALE - GraphicsManager::Camera().x,
        mPosition.y * TILE_SPRITE_SCALE - GraphicsManager::Camera().y,
        mSprite.srcRect.w * TILE_SPRITE_SCALE,
        mSprite.srcRect.h * TILE_SPRITE_SCALE,
        0xFFFFFFFF);*/

    SDL_Rect destRect =
    {
        mPosition.x * TILE_SPRITE_SCALE + mSprite.positionOffset.x * TILE_SPRITE_SCALE - GraphicsManager::Camera().x,
        mPosition.y * TILE_SPRITE_SCALE + mSprite.positionOffset.y * TILE_SPRITE_SCALE - GraphicsManager::Camera().y,
        mSprite.srcRect.w * TILE_SPRITE_SCALE,
        mSprite.srcRect.h * TILE_SPRITE_SCALE
    };

    GraphicsManager::DrawSpriteRect(mSpriteSheet, mSprite.srcRect, destRect);
}

void Actor::UpdateAnimation()
{
    Animation& anim = mAnimations[mCurrentAnimation];
    anim.currentFrame = ((SDL_GetTicks() - anim.startTime) * anim.frameRateSpeed / 1000) % anim.numFrames;

    mSprite.srcRect.x = anim.frames[anim.currentFrame].position.x;
    mSprite.srcRect.y = anim.frames[anim.currentFrame].position.y;
    mSprite.srcRect.w = anim.frames[anim.currentFrame].width;
    mSprite.srcRect.h = anim.frames[anim.currentFrame].height;
}