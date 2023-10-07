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
	void SetupInventoryPanel();
	void SetupJournalPanel();
	void SetupEquipPanel();

	void SetPanelState(EPanelState state);
	void FillPartyAttributes();
	void SetStatusButtonsText();
	void SetStatusCharacterAttributes(int index);

	void SetEquipButtonsText();

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

	UIPanel mStatusButtonPanel;
	UIButton mStatusButtonOne;
	UIButton mStatusButtonTwo;
	UIButton mStatusButtonThree;
	UIButton mStatusButtonFour;

	UIPanel mStatusAttributesPanel;
	UIText mStatusLevelText;
	UIText mStatusClassText;
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

	UIPanel mInventoryButtonsPanel;
	UIButton mInventoryButtonOne;
	UIButton mInventoryButtonTwo;
	UIButton mInventoryButtonThree;

	UIPanel mJournalButtonsPanel;
	UIButton mJournalButtonOne;
	UIButton mJournalButtonTwo;
	UIButton mJournalButtonThree;
	UIButton mJournalButtonFour;

	UIPanel mJournalKeywordsPanel;
	UIButton mKeywordsButtonOne;
	UIButton mKeywordsButtonTwo;
	UIButton mKeywordsButtonThree;
	UIButton mKeywordsButtonFour;

	UIPanel mEquipButtonsPanel;
	UIButton mEquipButtonOne;
	UIButton mEquipButtonTwo;
	UIButton mEquipButtonThree;
	UIButton mEquipButtonFour;

	UIPanel mEquipmentPanel;
	UIButton mEquipmentWeaponButton;
	UIButton mEquipmentShieldButton;
	UIButton mEquipmentHeadButton;
	UIButton mEquipmentChestButton;
	UIButton mEquipmentArmsButton;
	UIButton mEquipmentLegsButton;
	UIText mEquipmentWeaponText;
	UIText mEquipmentShieldText;
	UIText mEquipmentHeadText;
	UIText mEquipmentChestText;
	UIText mEquipmentArmsText;
	UIText mEquipmentLegsText;

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