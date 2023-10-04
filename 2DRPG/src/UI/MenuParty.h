#pragma once

#include "Menu.h"
#include "UIPanel.h"

#include "../Managers/PlayerManager.h"

#include "../Utils/Utils.h"

class MenuParty : public Menu
{
public:
	MenuParty();

	void Render(static SDL_Renderer* renderer) override;

	void FillPartyAttributes();

	bool mIsMainMenu = false;
	bool mCharacterSelected = false;
	int mFirstCharacterIndex = 0;

public:
	Vec2 mCharacterUIPositions[4] =
	{
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.2f),
		Vec2(1.0f, 1.2f)
	};

	UIPanel mMoneyPanel;

	UIPanel mMainPanel;
	UIButton mPartyButton;
	UIButton mStatusButton;
	UIButton mInventoryButton;
	UIButton mJournalButton;
	UIButton mEquipButton;
	UIButton mMagicButton;
	UIButton mExitButton;

	UIPanel mPartyPanel;
	UIButton mFirstCharacterButton;
	UIButton mSecondCharacterButton;
	UIButton mThirdCharacterButton;
	UIButton mFourthCharacterButton;

private:
	std::vector<UIButton*> mMainMenuButtons = 
	{
		&mPartyButton,
		&mStatusButton,
		&mInventoryButton,
		&mJournalButton,
		&mEquipButton,
		&mMagicButton,
		&mExitButton
	};
};