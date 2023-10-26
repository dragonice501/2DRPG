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
		PS_MAGIC,
		PS_SAVE,

		PS_SELECTING_WEAPON,
		PS_SELECTING_SHIELD,
		PS_SELECTING_ARMOUR_HEAD,
		PS_SELECTING_ARMOUR_CHEST,
		PS_SELECTING_ARMOUR_ARMS,
		PS_SELECTING_ARMOUR_LEGS
	};

	enum EEquipState
	{
		ES_EQUIPPING,
		ES_REMOVING
	};

public:
	MenuParty();

	void Render() override;

	void SetupMoneyPanel();
	void SetupMainPanel();
	void SetupPartyPanel();
	void SetupStatusPanel();
	void SetupInventoryPanel();
	void SetupJournalPanel();
	void SetupEquipPanel();
	void SetupSavePanel();

	void SetPanelState(EPanelState state);
	void FillPartyAttributes();
	void SetStatusButtonsText();
	void SetStatusCharacterAttributes(int index);

	void FillInventoryItemButtons();
	void FillInventoryWeaponsButtons();
	void FillInventoryShieldsButtons();
	void FillInventoryArmourButtons();
	void FillInventoryArmourHeadButtons();
	void FillInventoryArmourChestButtons();
	void FillInventoryArmourArmsButtons();
	void FillInventoryArmourLegsButtons();

	void FillJournalKeywordsButton(int index);

	void SetEquipButtonsText();
	void FillEquipmentText(int partyIndex);

	bool mIsMainMenu = false;
	bool mCharacterSelected = false;
	int mSelectedCharacterIndex = -1;

public:
	Vec2 mCharacterUIPositions[4] =
	{
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.2f),
		Vec2(1.0f, 1.2f)
	};

	EPanelState mPanelState = PS_PARTY;
	EEquipState mEquipState = ES_EQUIPPING;

	// Money Panel
	UIPanel mMoneyPanel;
	UIText mMoneyText;

	// Main Panel
	UIPanel mMainPanel;
	UIButton mPartyButton;
	UIButton mStatusButton;
	UIButton mInventoryButton;
	UIButton mJournalButton;
	UIButton mEquipButton;
	UIButton mMagicButton;
	UIButton mSaveButton;
	UIButton mExitButton;

	// Party Panel
	UIPanel mPartyPanel;
	UIButton mPartyButtonOne;
	UIButton mPartyButtonTwo;
	UIButton mPartyButtonThree;
	UIButton mPartyButtonFour;

	UIText mPartyLevelTextOne;
	UIText mPartyClassTextOne;
	UIText mPartyHPTextOne;
	UIText mPartyMPTextOne;

	UIText mPartyLevelTextTwo;
	UIText mPartyClassTextTwo;
	UIText mPartyHPTextTwo;
	UIText mPartyMPTextTwo;

	UIText mPartyLevelTextThree;
	UIText mPartyClassTextThree;
	UIText mPartyHPTextThree;
	UIText mPartyMPTextThree;

	UIText mPartyLevelTextFour;
	UIText mPartyClassTextFour;
	UIText mPartyHPTextFour;
	UIText mPartyMPTextFour;

	// Status Panel
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

	UIText mStatusLevelValueText;
	UIText mStatusHPValueText;
	UIText mStatusMPValueText;
	UIText mStatusCurrentXPValueText;
	UIText mStatusNextLevelValueText;
	UIText mStatusStrengthValueText;
	UIText mStatusDefenseValueText;
	UIText mStatusIntelligenceValueText;
	UIText mStatusSpeedValueText;
	UIText mStatusSkillValueText;
	UIText mStatusLuckValueText;

	// Inventory Panel
	UIPanel mInventoryButtonsPanel;
	UIButton mInventoryButtonWeapons;
	UIButton mInventoryButtonArmour;
	UIButton mInventoryButtonItems;

	UIPanel mInventoryPanel;
	UIButton mInventoryPanelButtonOne;
	UIButton mInventoryPanelButtonTwo;
	UIButton mInventoryPanelButtonThree;
	UIButton mInventoryPanelButtonFour;

	// Journal Panel
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

	// Equip Panel
	UIPanel mEquipButtonsPanel;
	UIButton mEquipButtonOne;
	UIButton mEquipButtonTwo;
	UIButton mEquipButtonThree;
	UIButton mEquipButtonFour;

	UIPanel mEquipOptionsPanel;
	UIButton mEquipOptionsButtonEquip;
	UIButton mEquipOptionsButtonRemove;
	UIButton mEquipOptionsButtonRemoveAll;
	UIButton mEquipOptionsButtonOptimize;

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

	// Save Panel
	UIPanel mSavePromptPanel;
	UIText mSavePromptText;

	UIPanel mSaveButtonsPanel;
	UIButton mSaveButtonYes;
	UIButton mSaveButtonNo;

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