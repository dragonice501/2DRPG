#pragma once

#include "Menu.h"

class MenuMainMenu : public Menu
{
public:
	MenuMainMenu();

	virtual void Render() override;

	void SetupNewGamePanel();
	void SetupContinuePanel();
	void SetupQuitPanel();

private:
	UIPanel mNewGamePanel;
	UIButton mNewGameButton;

	UIPanel mContinePanel;
	UIButton mContinueButton;

	UIPanel mQuitPanel;
	UIButton mQuitButton;
};