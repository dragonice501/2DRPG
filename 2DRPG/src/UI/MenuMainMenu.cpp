#include "MenuMainMenu.h"

MenuMainMenu::MenuMainMenu()
{
	SetupNewGamePanel();
	SetupNewCharacterPanels();
	SetupContinuePanel();
	SetupQuitPanel();

	mCurrentButton = &mNewGameButton;
}

void MenuMainMenu::Render()
{
	switch (mMenuState)
	{
		case MenuMainMenu::EM_MAIN:
		{
			if (mNewGamePanel.mIsActive)
			{
				mNewGamePanel.Render();
			}

			if (mContinePanel.mIsActive)
			{
				mContinePanel.Render();
			}

			if (mQuitPanel.mIsActive)
			{
				mQuitPanel.Render();
			}
			break;
		}
		case MenuMainMenu::EM_NEW_GAME:
		{
			if (mNewCharacterPanelOne.mIsActive)
			{
				mNewCharacterPanelOne.Render();
			}

			if (mNewCharacterPanelTwo.mIsActive)
			{
				mNewCharacterPanelTwo.Render();
			}

			if (mNewCharacterPanelThree.mIsActive)
			{
				mNewCharacterPanelThree.Render();
			}

			if (mNewCharacterPanelFour.mIsActive)
			{
				mNewCharacterPanelFour.Render();
			}

			if (mNewCharacterNamePanelOne.mIsActive)
			{
				mNewCharacterNamePanelOne.Render();
			}

			if (mNewCharacterNamePanelTwo.mIsActive)
			{
				mNewCharacterNamePanelTwo.Render();
			}

			if (mNewCharacterNamePanelThree.mIsActive)
			{
				mNewCharacterNamePanelThree.Render();
			}

			if (mNewCharacterNamePanelFour.mIsActive)
			{
				mNewCharacterNamePanelFour.Render();
			}
			break;
		}
	}
}

void MenuMainMenu::SetupNewGamePanel()
{
	int textSize = Font::GetStringFontLength("New Game");
	mNewGamePanel.mIsActive = true;
	mNewGamePanel.mPosition = Vec2(GraphicsManager::WindowWidth() * 0.5f - (textSize * 0.5f) * TEXT_SIZE - TEXT_PADDING, GraphicsManager::WindowHeight() * 0.5f);
	mNewGamePanel.mPosition = CalcWindowUVFromPosition(mNewGamePanel.mPosition);
	mNewGamePanel.mSize = Vec2(textSize * TEXT_SIZE + TEXT_PADDING * 2.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f);

	mNewGameButton.mPosition = CalcWindowPositionFromUV(mNewGamePanel.mPosition) + Vec2(TEXT_PADDING);
	mNewGameButton.mText = "New Game";

	mNewGameButton.OnDownAction = [this]()
	{
		mCurrentButton = &mContinueButton;
	};
	mNewGameButton.OnAcceptAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		mCurrentButton = &mNewCharacterButtonOne;
	};

	mNewGamePanel.mButtons.push_back(&mNewGameButton);
}

void MenuMainMenu::SetupNewCharacterPanels()
{
	mNewCharacterPanelOne.mIsActive = true;
	mNewCharacterPanelOne.mPosition =
		Vec2(
			GraphicsManager::WindowWidth() * 0.5f, GraphicsManager::WindowHeight() * 0.5f) +
		Vec2(-128 - UI_BOX_BORDER_SIZE - 64, -128 - UI_BOX_BORDER_SIZE - 64);
	mNewCharacterPanelOne.mPosition = CalcWindowUVFromPosition(mNewCharacterPanelOne.mPosition);
	mNewCharacterPanelOne.mSize = { 128, 128 };

	mNewCharacterNamePanelOne.mIsActive = true;
	mNewCharacterNamePanelOne.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelOne.mPosition) + Vec2(0.0f, mNewCharacterPanelOne.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mNewCharacterNamePanelOne.mPosition = CalcWindowUVFromPosition(mNewCharacterNamePanelOne.mPosition);
	mNewCharacterNamePanelOne.mSize = { mNewCharacterPanelOne.mSize.x, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f };

	mNewCharacterPanelTwo.mIsActive = true;
	mNewCharacterPanelTwo.mPosition =
		Vec2(
			GraphicsManager::WindowWidth() * 0.5f, GraphicsManager::WindowHeight() * 0.5f) +
		Vec2(128 + UI_BOX_BORDER_SIZE - 64, -128 - UI_BOX_BORDER_SIZE - 64);
	mNewCharacterPanelTwo.mPosition = CalcWindowUVFromPosition(mNewCharacterPanelTwo.mPosition);
	mNewCharacterPanelTwo.mSize = { 128, 128 };

	mNewCharacterNamePanelTwo.mIsActive = true;
	mNewCharacterNamePanelTwo.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelTwo.mPosition) + Vec2(0.0f, mNewCharacterPanelTwo.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mNewCharacterNamePanelTwo.mPosition = CalcWindowUVFromPosition(mNewCharacterNamePanelTwo.mPosition);
	mNewCharacterNamePanelTwo.mSize = { mNewCharacterPanelTwo.mSize.x, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f };

	mNewCharacterPanelThree.mIsActive = true;
	mNewCharacterPanelThree.mPosition =
		Vec2(
			GraphicsManager::WindowWidth() * 0.5f, GraphicsManager::WindowHeight() * 0.5f) +
		Vec2(-128 - UI_BOX_BORDER_SIZE - 64, 128 + UI_BOX_BORDER_SIZE - 64);
	mNewCharacterPanelThree.mPosition = CalcWindowUVFromPosition(mNewCharacterPanelThree.mPosition);
	mNewCharacterPanelThree.mSize = { 128, 128 };

	mNewCharacterNamePanelThree.mIsActive = true;
	mNewCharacterNamePanelThree.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelThree.mPosition) + Vec2(0.0f, mNewCharacterPanelThree.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mNewCharacterNamePanelThree.mPosition = CalcWindowUVFromPosition(mNewCharacterNamePanelThree.mPosition);
	mNewCharacterNamePanelThree.mSize = { mNewCharacterPanelThree.mSize.x, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f };

	mNewCharacterPanelFour.mIsActive = true;
	mNewCharacterPanelFour.mPosition =
		Vec2(
			GraphicsManager::WindowWidth() * 0.5f, GraphicsManager::WindowHeight() * 0.5f) +
		Vec2(128 + UI_BOX_BORDER_SIZE - 64, 128 + UI_BOX_BORDER_SIZE - 64);
	mNewCharacterPanelFour.mPosition = CalcWindowUVFromPosition(mNewCharacterPanelFour.mPosition);
	mNewCharacterPanelFour.mSize = { 128, 128 };

	mNewCharacterNamePanelFour.mIsActive = true;
	mNewCharacterNamePanelFour.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelFour.mPosition) + Vec2(0.0f, mNewCharacterPanelFour.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mNewCharacterNamePanelFour.mPosition = CalcWindowUVFromPosition(mNewCharacterNamePanelFour.mPosition);
	mNewCharacterNamePanelFour.mSize = { mNewCharacterPanelFour.mSize.x, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f };

	mNewCharacterButtonOne.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelOne.mPosition) + Vec2(0.0f, 64);
	mNewCharacterButtonOne.mText = "Character One";

	mNewCharacterButtonTwo.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelTwo.mPosition) + Vec2(0.0f, 64);
	mNewCharacterButtonTwo.mText = "Character Two";

	mNewCharacterButtonThree.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelThree.mPosition) + Vec2(0.0f, 64);
	mNewCharacterButtonThree.mText = "Character Three";

	mNewCharacterButtonFour.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelFour.mPosition) + Vec2(0.0f, 64);
	mNewCharacterButtonFour.mText = "Character Four";

	mNewCharacterNameButtonOne.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelOne.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonOne.mText = "Name One";

	mNewCharacterNameButtonTwo.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelTwo.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonTwo.mText = "Name Two";

	mNewCharacterNameButtonThree.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelThree.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonThree.mText = "Name Three";

	mNewCharacterNameButtonFour.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelFour.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonFour.mText = "Name Four";

	mNewCharacterButtonOne.OnRightAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonTwo;
	};
	mNewCharacterButtonOne.OnDownAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonOne;
	};
	mNewCharacterButtonOne.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterNameButtonOne.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonOne;
	};
	mNewCharacterNameButtonOne.OnRightAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonTwo;
	};
	mNewCharacterNameButtonOne.OnDownAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonThree;
	};
	mNewCharacterNameButtonOne.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterButtonTwo.OnLeftAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonOne;
	};
	mNewCharacterButtonTwo.OnDownAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonTwo;
	};
	mNewCharacterButtonTwo.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterNameButtonTwo.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonTwo;
	};
	mNewCharacterNameButtonTwo.OnLeftAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonOne;
	};
	mNewCharacterNameButtonTwo.OnDownAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonFour;
	};
	mNewCharacterNameButtonTwo.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterButtonThree.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonOne;
	};
	mNewCharacterButtonThree.OnRightAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonFour;
	};
	mNewCharacterButtonThree.OnDownAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonThree;
	};
	mNewCharacterButtonThree.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterNameButtonThree.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonThree;
	};
	mNewCharacterNameButtonThree.OnRightAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonFour;
	};
	mNewCharacterNameButtonThree.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterButtonFour.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonTwo;
	};
	mNewCharacterButtonFour.OnLeftAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonThree;
	};
	mNewCharacterButtonFour.OnDownAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonFour;
	};
	mNewCharacterButtonFour.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterNameButtonFour.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonFour;
	};
	mNewCharacterNameButtonFour.OnLeftAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonThree;
	};
	mNewCharacterNameButtonFour.OnCancelAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mNewCharacterPanelOne.mButtons.push_back(&mNewCharacterButtonOne);
	mNewCharacterNamePanelOne.mButtons.push_back(&mNewCharacterNameButtonOne);

	mNewCharacterPanelTwo.mButtons.push_back(&mNewCharacterButtonTwo);
	mNewCharacterNamePanelTwo.mButtons.push_back(&mNewCharacterNameButtonTwo);

	mNewCharacterPanelThree.mButtons.push_back(&mNewCharacterButtonThree);
	mNewCharacterNamePanelThree.mButtons.push_back(&mNewCharacterNameButtonThree);

	mNewCharacterPanelFour.mButtons.push_back(&mNewCharacterButtonFour);
	mNewCharacterNamePanelFour.mButtons.push_back(&mNewCharacterNameButtonFour);
}

void MenuMainMenu::SetupContinuePanel()
{
	int textSize = Font::GetStringFontLength("Continue");
	mContinePanel.mIsActive = true;
	mContinePanel.mPosition = CalcWindowPositionFromUV(mNewGamePanel.mPosition) + Vec2(0.0f, mNewGamePanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mContinePanel.mPosition = CalcWindowUVFromPosition(mContinePanel.mPosition);
	mContinePanel.mSize = Vec2(textSize * TEXT_SIZE + TEXT_PADDING * 2.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f);

	mContinueButton.mPosition = CalcWindowPositionFromUV(mContinePanel.mPosition) + Vec2(TEXT_PADDING);
	mContinueButton.mText = "Continue";

	mContinueButton.OnUpAction = [this]()
	{
		mCurrentButton = &mNewGameButton;
	};
	mContinueButton.OnDownAction = [this]()
	{
		mCurrentButton = &mQuitButton;
	};
	mContinueButton.OnAcceptAction = [this]()
	{
		GameManager::LoadGameSave();
		PlayerManager::LoadCharacters();
	};

	mContinePanel.mButtons.push_back(&mContinueButton);
}

void MenuMainMenu::SetupQuitPanel()
{
	int textSize = Font::GetStringFontLength("Continue");
	mQuitPanel.mIsActive = true;
	mQuitPanel.mPosition = CalcWindowPositionFromUV(mContinePanel.mPosition) + Vec2(0.0f, mContinePanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mQuitPanel.mPosition = CalcWindowUVFromPosition(mQuitPanel.mPosition);
	mQuitPanel.mSize = Vec2(textSize * TEXT_SIZE + TEXT_PADDING * 2.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f);

	mQuitButton.mPosition = CalcWindowPositionFromUV(mQuitPanel.mPosition) + Vec2(TEXT_PADDING);
	mQuitButton.mText = "  Quit";

	mQuitButton.OnUpAction = [this]()
	{
		mCurrentButton = &mContinueButton;
	};
	mQuitButton.OnAcceptAction = [this]()
	{
		GameManager::QuitGame();
	};

	mQuitPanel.mButtons.push_back(&mQuitButton);
}
