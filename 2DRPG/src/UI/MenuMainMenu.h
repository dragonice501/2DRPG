#pragma once

#include "Menu.h"

class MenuMainMenu : public Menu
{
private:
	enum EMainState
	{
		EM_MAIN,
		EM_NEW_GAME,
		EM_SELECTING_NAME,
		EM_SELECTING_CHARACTER
	};

public:
	MenuMainMenu();

	virtual void Render() override;

	void LoadMainMenu();

	void SetupMainPanels();
	void SetupNewCharacterPanels();
	void SetupNewCharacterClassSprites();
	void SetupSelectNamePanel();
	void SetupNewNamePanel();
	void SetupFinishPanel();

	void IncrementCharacterClass(int partyIndex);
	void DecrementCharacterClass(int partyIndex);

	void SetNewNameText();
	void AddLetterToNewName(const char character);
	void ReturnNewName();

private:
	EMainState mMenuState = EM_MAIN;

	// Main Menu
	UIPanel mNewGamePanel;
	UIButton mNewGameButton;
	
	UIPanel mContinePanel;
	UIButton mContinueButton;

	UIPanel mQuitPanel;
	UIButton mQuitButton;

	// New Game
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

	UIButton* mCharacterClassButtons[4] =
	{
		&mNewCharacterButtonOne,
		&mNewCharacterButtonTwo,
		&mNewCharacterButtonThree,
		&mNewCharacterButtonFour
	};

	UISprite mNewCharacterClassOne;
	UISprite mNewCharacterClassTwo;
	UISprite mNewCharacterClassThree;
	UISprite mNewCharacterClassFour;

	UISprite* mCharacterClasses[4] =
	{
		&mNewCharacterClassOne,
		&mNewCharacterClassTwo,
		&mNewCharacterClassThree,
		&mNewCharacterClassFour
	};

	std::string mClasses[4] =
	{
		"Dancer",
		"Knight",
		"Mage",
		"Paladin"
	};

	int mNewCharacterClasses[4] = { 3, 0, 1, 2 };
	int mNewCharacterClassIndex = 0;

	std::string* mNewCharacterNames[4] =
	{
		&mNewCharacterNameButtonOne.mText,
		&mNewCharacterNameButtonTwo.mText,
		&mNewCharacterNameButtonThree.mText,
		&mNewCharacterNameButtonFour.mText,
	};
	int mCurrentNewNameIndex = -1;

	UIPanel mFinishPanel;
	UIButton mFinishButton;

	UIPanel mBackPanel;
	UIButton mBackButton;

	UIPanel mNewNamePanel;
	UIText mNewNamePanelText;

	std::string* mNewCharacterName = &mNewNamePanelText.mText;
	std::string mNewNamePlaceholder;

	UIPanel mSelectLetterPanel;

	UIButton mSelectLetterEraseButton;
	UIButton mSelectLetterEndButton;

	UIButton mSelectLetterAButton;
	UIButton mSelectLetterBButton;
	UIButton mSelectLetterCButton;
	UIButton mSelectLetterDButton;
	UIButton mSelectLetterEButton;
	UIButton mSelectLetterFButton;
	UIButton mSelectLetterGButton;
	UIButton mSelectLetterHButton;
	UIButton mSelectLetterIButton;
	UIButton mSelectLetterJButton;
	UIButton mSelectLetterKButton;
	UIButton mSelectLetterLButton;
	UIButton mSelectLetterMButton;
	
	UIButton mSelectLetterNButton;
	UIButton mSelectLetterOButton;
	UIButton mSelectLetterPButton;
	UIButton mSelectLetterQButton;
	UIButton mSelectLetterRButton;
	UIButton mSelectLetterSButton;
	UIButton mSelectLetterTButton;
	UIButton mSelectLetterUButton;
	UIButton mSelectLetterVButton;
	UIButton mSelectLetterWButton;
	UIButton mSelectLetterXButton;
	UIButton mSelectLetterYButton;
	UIButton mSelectLetterZButton;

	UIButton mSelectLetteraButton;
	UIButton mSelectLetterbButton;
	UIButton mSelectLettercButton;
	UIButton mSelectLetterdButton;
	UIButton mSelectLettereButton;
	UIButton mSelectLetterfButton;
	UIButton mSelectLettergButton;
	UIButton mSelectLetterhButton;
	UIButton mSelectLetteriButton;
	UIButton mSelectLetterjButton;
	UIButton mSelectLetterkButton;
	UIButton mSelectLetterlButton;
	UIButton mSelectLettermButton;

	UIButton mSelectLetternButton;
	UIButton mSelectLetteroButton;
	UIButton mSelectLetterpButton;
	UIButton mSelectLetterqButton;
	UIButton mSelectLetterrButton;
	UIButton mSelectLettersButton;
	UIButton mSelectLettertButton;
	UIButton mSelectLetteruButton;
	UIButton mSelectLettervButton;
	UIButton mSelectLetterwButton;
	UIButton mSelectLetterxButton;
	UIButton mSelectLetteryButton;
	UIButton mSelectLetterzButton;
};