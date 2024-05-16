#pragma once

#include "GameObject.h"

#include "PlayerManager.h"

class Npc : public GameObject
{
public:
	void Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startingAnimation = "IdleDown");

	void Input() override;
	void Update(float dt) override;
	void Render() override;

	void LoadAnimations(std::string animationsFilePath);

	void UpdateAnimation();

	void DestroySpriteSheet() { SDL_DestroyTexture(mSpriteSheet); }

	const Vec2& GetPosition() const { return mPosition; }

	inline void SetCurrentAnimation(const std::string& animation) { mCurrentAnimation = animation; }

	EDialogueType GetDialogueState() const { return mCurrentDialogueMode; }

	const std::vector<std::string>& GetCurrentDialogue() const;
	const std::string GetKeyword() const { return mInformationMap.begin()->first; }
	const EJournalType GetKeywordType();

	void SetDialogueMode(const EDialogueType dialogueMode) { mCurrentDialogueMode = dialogueMode; }
	void SetAnswerKey(const std::string& keyword) { mCurrentAnswerKey = keyword; }

	bool CycleThroughDialogue();

	void LoadDialogue(const std::string filePathName);
	bool HasNewInformation();
	bool HasAnswerToKeyword(const std::string& keyword);

public:
	SpriteComponent mSprite;
	std::string mAssetID;
	SDL_Texture* mSpriteSheet;

	Vec2 mPosition;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation;

	std::map<std::string, std::vector<std::vector<std::string>>> mDialogueMap;
	std::map<std::string, std::vector<std::vector<std::string>>> mInformationMap;
	std::map<std::string, std::vector<std::vector<std::string>>> mAnswersMap;

	std::map<std::string, EJournalType> mKeywordType;

	std::string mCurrentDialogueKey;
	std::string mCurrentInformationKey;
	std::string mCurrentAnswerKey;
	int mCurrentDialogueIndex = 0;

	EDialogueType mCurrentDialogueMode = ED_NONE;
};

