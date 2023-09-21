#pragma once

#include "UIButton.h"

#include "../Managers/GameManager.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/PlayerManager.h"
#include "../Graphics/Font.h"

#include "../Utils/Vec2.h"

#include <SDL.h>
#include <vector>

class PartyMenu
{
public:
	PartyMenu();

	const UIButton& GetCurrentButton() const { return *mCurrentButton; }
	void SetCurrentButton(UIButton* button) { mCurrentButton = button; }

	void Render(static SDL_Renderer* renderer);

public:
	UIButton* mCurrentButton;

	Vec2 mCharacterUIPositions[4] =
	{
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.2f),
		Vec2(1.0f, 1.2f)
	};

	// Main Menu Buttons
	UIButton mPartyButton = UIButton("Party");
	UIButton mStatusButton = UIButton("Status");
	UIButton mInventoryButton = UIButton("Inventory");
	UIButton mJournalButton = UIButton("Journal");
	UIButton mEquipButton = UIButton("Equip");
	UIButton mMagicButton = UIButton("Magic");
	UIButton mExitButton = UIButton("Exit");

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

	int value = 1234;
};