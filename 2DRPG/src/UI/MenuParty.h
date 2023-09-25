#pragma once

#include "Menu.h"

class MenuParty : public Menu
{
public:
	MenuParty();

	void Render(static SDL_Renderer* renderer) override;

	bool mIsMainMenu = false;

public:
	Vec2 mCharacterUIPositions[4] =
	{
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.2f),
		Vec2(1.0f, 1.2f)
	};

	UIPanel mMainPanel;
	UIButton mPartyButton = UIButton("Party");
	UIButton mStatusButton = UIButton("Status");
	UIButton mInventoryButton = UIButton("Inventory");
	UIButton mJournalButton = UIButton("Journal");
	UIButton mEquipButton = UIButton("Equip");
	UIButton mMagicButton = UIButton("Magic");
	UIButton mExitButton = UIButton("Exit");
	int mMainButtonIndex = 0;

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