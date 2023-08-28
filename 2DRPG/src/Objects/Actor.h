#pragma once

#include "Components.h"
#include "../Utils/Vec2.h"
#include "../Utils/Constants.h"

#include "../Engine/Engine.h"
#include "../Managers/GraphicsManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <fstream>

class Actor
{
public:
	Actor();
	~Actor();

	virtual void Init(const std::string& spriteSheetPath, const std::string& animationsFilePath, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startinAnimation = "IdleDown");
	virtual void LoadAnimations(std::string animationsFilePath);

	virtual void Update(const float dt);
	virtual void Render(SDL_Renderer* renderer);

	virtual void UpdateAnimation();

	virtual const Vec2& GetPosition() const { return mPosition; }
	const std::string& GetDialogue() const { return mDialogueMap.at(mCurrentDialogueKey)[mCurrentDialogueIndex]; }
	bool CycleThroughDialogue();

	void LoadDialogue(const std::string filePathName);

protected:
	Vec2 mPosition;
	Sprite mSprite;
	SDL_Texture* mSpriteSheet;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;

	std::map<std::string, std::vector<std::string>> mDialogueMap;
	std::map<std::string, std::vector<std::string>> mAnswersMap;

	std::string mCurrentDialogueKey = "Greeting";
	int mCurrentDialogueIndex = 0;
};