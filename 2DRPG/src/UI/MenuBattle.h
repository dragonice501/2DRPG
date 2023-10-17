#pragma once

#include "Menu.h"

class MenuBattle : public Menu
{
public:
	MenuBattle();

	void Render() override;

	void SetupActionsPanel();
	void SetupPartyPanel();

	UIPanel mPartyActionPanel;
	UIButton mFightButton;
	UIButton mMagicButton;
	UIButton mItemButton;
	UIButton mRunButton;

	UIPanel mPartyStatsPanel;
	UIText mPartyNamesOne;
	UIText mPartyNamesTwo;
	UIText mPartyNamesThree;
	UIText mPartyNamesFour;
	UIText mPartyStatsTextOne;
	UIText mPartyStatsTextTwo;
	UIText mPartyStatsTextThree;
	UIText mPartyStatsTextFour;

	std::vector<UIButton> mSmallEnemyButtons;
};