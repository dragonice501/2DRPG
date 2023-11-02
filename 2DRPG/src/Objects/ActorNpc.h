#pragma once
#include "Actor.h"

#include "../Managers/PlayerManager.h"

class ActorNpc : public Actor
{
public:
	void Init(const std::string& name, const Vec2& spawnPosition, SDL_Renderer* renderer, std::string startingAnimation = "IdleDown") override;
	void Update(const float dt) override;

	void Render() override;

	void LoadAnimations(std::string animationsFilePath);

	void UpdateAnimation();

	void DestroySpriteSheet() { SDL_DestroyTexture(mSpriteSheet); }

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
	Sprite mSprite;
	std::string mAssetID;
	SDL_Texture* mSpriteSheet;

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

