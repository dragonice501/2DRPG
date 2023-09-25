#pragma once

#include "Menu.h"

class MenuBattle : public Menu
{
public:
	MenuBattle();

	void Render(static SDL_Renderer* renderer) override;

	UIPanel mPartyActionPanel;
	UIButton mFightButton;
	UIButton mMagicButton;
	UIButton mItemButton;
	UIButton mRunButton;

	UIPanel mPartyStatsPanel;
};