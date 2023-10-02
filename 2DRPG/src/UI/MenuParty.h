#pragma once

#include "Menu.h"
#include "UIPanel.h"

class MenuParty : public Menu
{
public:
	MenuParty();

	void Render(static SDL_Renderer* renderer) override;

	bool mIsMainMenu = false;

public:
	enum PartyMenuState
	{
		MAIN,
		PARTY,
		STATUS,
		INVENTORY,
		JOURNAL,
		EQUIP,
		MAGIC
	};

	PartyMenuState mMenuState;

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
	int mMainButtonIndex = 0;

	UIPanel mPartyPanel;

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