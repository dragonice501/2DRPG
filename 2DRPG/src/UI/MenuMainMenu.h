#pragma once

#include "Menu.h"

class MenuMainMenu : public Menu
{
private:
	enum EMainState
	{
		EM_MAIN,
		EM_NEW_GAME
	};

public:
	MenuMainMenu();

	virtual void Render() override;

	void SetupNewGamePanel();
	void SetupNewCharacterPanels();
	void SetupContinuePanel();
	void SetupQuitPanel();

private:
	EMainState mMenuState = EM_MAIN;

	UIPanel mNewGamePanel;
	UIButton mNewGameButton;

	UIPanel mNewCharacterPanelOne;
	UIButton mNewCharacterButtonOne;

	UIPanel mNewCharacterNamePanelOne;
	UIButton mNewCharacterNameButtonOne;

	UIPanel mNewCharacterPanelTwo;
	UIButton mNewCharacterButtonTwo;

	UIPanel mNewCharacterNamePanelTwo;
	UIButton mNewCharacterNameButtonTwo;

	UIPanel mNewCharacterPanelThree;
	UIButton mNewCharacterButtonThree;

	UIPanel mNewCharacterNamePanelThree;
	UIButton mNewCharacterNameButtonThree;

	UIPanel mNewCharacterPanelFour;
	UIButton mNewCharacterButtonFour;

	UIPanel mNewCharacterNamePanelFour;
	UIButton mNewCharacterNameButtonFour;

	UIPanel mContinePanel;
	UIButton mContinueButton;

	UIPanel mQuitPanel;
	UIButton mQuitButton;
};