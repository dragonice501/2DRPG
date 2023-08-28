#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init(const std::string& spriteSheetPath, const std::string& animationsFilePath, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation)
{
    std::string filePath = "./assets/" + spriteSheetPath + ".png";
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface)
    {
        mSpriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    }

    mPosition = spawnPosition;
    mSprite = { 32, 32, 0, -16, 0, 64 };

    LoadAnimations(animationsFilePath);
    mCurrentAnimation = startinAnimation;
}

void Actor::LoadAnimations(std::string animationsFilePath)
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

void Actor::Update(const float dt)
{
    UpdateAnimation();
}

void Actor::Render(SDL_Renderer* renderer)
{
    SDL_Rect destRect =
    {
        mPosition.x * TILE_SPRITE_SCALE + mSprite.xOffset * TILE_SPRITE_SCALE - GraphicsManager::Camera().x,
        mPosition.y * TILE_SPRITE_SCALE + mSprite.yOffset * TILE_SPRITE_SCALE - GraphicsManager::Camera().y,
        mSprite.width * TILE_SPRITE_SCALE,
        mSprite.height * TILE_SPRITE_SCALE
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

bool Actor::CycleThroughDialogue()
{
    mCurrentDialogueIndex++;
    if (mCurrentDialogueIndex >= mDialogueMap[mCurrentDialogueKey].size())
    {
        mCurrentDialogueIndex = 0;
        return false;
    }

    return true;
}

void Actor::LoadDialogue(const std::string filePathName)
{
    std::string dialogueType;
    std::string dialogueAnswer;
    std::string diaglogue;
    std::vector<std::string> stringVec;

    std::vector<std::string> dialogueVec;

    std::string  fileName = "./assets/" + filePathName + ".txt";
    std::ifstream file(fileName);
    std::string text;
    while (file >> text)
    {
        if (text == "Start")
        {
            file >> dialogueType;
            continue;
        }
        else if (text == "Answer")
        {
            file >> dialogueAnswer;
            continue;
        }
        else if (text == "End")
        {
            if (dialogueAnswer != "")
            {
                mAnswersMap.emplace(dialogueAnswer, stringVec);
            }
            else
            {
                mDialogueMap.emplace(dialogueType, stringVec);
                mGreetingDialogue.emplace(dialogueType, dialogueVec);
            }

            stringVec.clear();
            dialogueVec.clear();

            dialogueType.clear();
            dialogueAnswer.clear();
        }
        else
        {
            std::string newDialogue;
            std::string string;
            std::getline(file, string);

            newDialogue = text + string;

            for (int i = 0, j = i; i <= newDialogue.size(); i++)
            {
                if (newDialogue[i] == ' ')
                {
                    std::string string = newDialogue.substr(j, (i) - j);
                    j = i + 1;

                    dialogueVec.push_back(string);
                }

                if (i == newDialogue.size())
                {
                    std::string string = newDialogue.substr(j, i - j);

                    dialogueVec.push_back(string);
                }
            }

            stringVec.push_back(newDialogue);
        }
    }
}