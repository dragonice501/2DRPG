#pragma once
#include "Actor.h"

#include "../Managers/PlayerManager.h"

class ActorNpc : public Actor
{
private:

public:
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
