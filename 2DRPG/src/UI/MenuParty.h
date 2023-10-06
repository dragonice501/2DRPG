#pragma once

#include "Menu.h"
#include "UIPanel.h"

#include "../Managers/PlayerManager.h"

#include "../Utils/Utils.h"

class MenuParty : public Menu
{
private:
	enum EPanelState
	{
		PS_PARTY,
		PS_STATUS,
		PS_INVENTORY,
		PS_JOURNAL,
		PS_EQUIP,
		PS_MAGIC
	};

public:
	MenuParty();

	void Render(static SDL_Renderer* renderer) override;

	void SetupMoneyPanel();
	void SetupMainPanel();
	void SetupPartyPanel();
	void SetupStatusPanel();

	void SetPanelState(EPanelState state);
	void FillPartyAttributes();
	void SetStatusButtonsText();
	void SetStatusCharacterAttributes(int index);

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

	EPanelState mPanelState = PS_PARTY;

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
	UIButton mPartyButtonOne;
	UIButton mPartyButtonTwo;
	UIButton mPartyButtonThree;
	UIButton mPartyButtonFour;

	UIPanel mStatusPanel;
	UIButton mStatusButtonOne;
	UIButton mStatusButtonTwo;
	UIButton mStatusButtonThree;
	UIButton mStatusButtonFour;

	UIText mStatusLevelText;
	UIText mStatusHPText;
	UIText mStatusMPText;
	UIText mStatusCurrentXPText;
	UIText mStatusNextLevelText;
	UIText mStatusStrengthText;
	UIText mStatusDefenseText;
	UIText mStatusIntelligenceText;
	UIText mStatusSpeedText;
	UIText mStatusSkillText;
	UIText mStatusLuckText;

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