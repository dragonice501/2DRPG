#include "MenuMainMenu.h"

MenuMainMenu::MenuMainMenu()
{
	SetupNewGamePanel();
	SetupNewCharacterPanels();
	SetupNewCharacterClassSprites();
	SetupSelectNamePanel();
	SetupNewNamePanel();
	SetupFinishPanel();

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

			if (mFinishPanel.mIsActive)
			{
				mFinishPanel.Render();
			}

			if (mBackPanel.mIsActive)
			{
				mBackPanel.Render();
			}

			mNewCharacterClassOne.Render();
			mNewCharacterClassTwo.Render();
			mNewCharacterClassThree.Render();
			mNewCharacterClassFour.Render();
			break;
		}
		case MenuMainMenu::EM_SELECTING_NAME:
		{
			if (mSelectLetterPanel.mIsActive)
			{
				mSelectLetterPanel.Render();
			}

			if (mNewNamePanel.mIsActive)
			{
				mNewNamePanel.Render();
			}
			break;
		}
		case MenuMainMenu::EM_SELECTING_CHARACTER:
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

			if (mFinishPanel.mIsActive)
			{
				mFinishPanel.Render();
			}

			if (mBackPanel.mIsActive)
			{
				mBackPanel.Render();
			}

			mNewCharacterClassOne.Render();
			mNewCharacterClassTwo.Render();
			mNewCharacterClassThree.Render();
			mNewCharacterClassFour.Render();
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

	mNewCharacterButtonOne.mPosition =
		CalcWindowPositionFromUV(mNewCharacterPanelOne.mPosition) +
		Vec2(TEXT_PADDING, mNewCharacterPanelOne.mSize.y - Font::fontHeight * TEXT_SIZE - TEXT_PADDING);
	mNewCharacterButtonOne.mText = mClasses[mNewCharacterClasses[0]];

	mNewCharacterButtonTwo.mPosition =
		CalcWindowPositionFromUV(mNewCharacterPanelTwo.mPosition) +
		Vec2(TEXT_PADDING, mNewCharacterPanelOne.mSize.y - Font::fontHeight * TEXT_SIZE - TEXT_PADDING);
	mNewCharacterButtonTwo.mText = mClasses[mNewCharacterClasses[1]];

	mNewCharacterButtonThree.mPosition =
		CalcWindowPositionFromUV(mNewCharacterPanelThree.mPosition) +
		Vec2(TEXT_PADDING, mNewCharacterPanelOne.mSize.y - Font::fontHeight * TEXT_SIZE - TEXT_PADDING);
	mNewCharacterButtonThree.mText = mClasses[mNewCharacterClasses[2]];

	mNewCharacterButtonFour.mPosition =
		CalcWindowPositionFromUV(mNewCharacterPanelFour.mPosition) +
		Vec2(TEXT_PADDING, mNewCharacterPanelOne.mSize.y - Font::fontHeight * TEXT_SIZE - TEXT_PADDING);
	mNewCharacterButtonFour.mText = mClasses[mNewCharacterClasses[3]];

	mNewCharacterNameButtonOne.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelOne.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonOne.mText = "Name";

	mNewCharacterNameButtonTwo.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelTwo.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonTwo.mText = "Name";

	mNewCharacterNameButtonThree.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelThree.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonThree.mText = "Name";

	mNewCharacterNameButtonFour.mPosition = CalcWindowPositionFromUV(mNewCharacterNamePanelFour.mPosition) + Vec2(TEXT_PADDING);
	mNewCharacterNameButtonFour.mText = "Name";

	mNewCharacterButtonOne.OnLeftAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			DecrementCharacterClass(0);
		}
	};
	mNewCharacterButtonOne.OnRightAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			IncrementCharacterClass(0);
		}
		else
		{
			mCurrentButton = &mNewCharacterButtonTwo;
		}
	};
	mNewCharacterButtonOne.OnDownAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER) return;

		mCurrentButton = &mNewCharacterNameButtonOne;
	};
	mNewCharacterButtonOne.OnAcceptAction = [this]()
	{
		if (mMenuState == EM_NEW_GAME)
		{
			mNewCharacterClassIndex = 0;
			mMenuState = EM_SELECTING_CHARACTER;
		}
		else mMenuState = EM_NEW_GAME;
	};
	mNewCharacterButtonOne.OnCancelAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			mMenuState = EM_NEW_GAME;
			return;
		}
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
	mNewCharacterNameButtonOne.OnAcceptAction = [this]()
	{
		mCurrentNewNameIndex = 0;
		*mNewCharacterName = "";
		mNewNamePlaceholder = *mNewCharacterNames[mCurrentNewNameIndex];

		mMenuState = EM_SELECTING_NAME;
		mCurrentButton = &mSelectLetterAButton;
		mPreviousButtonFirst = &mNewCharacterNameButtonOne;
	};


	mNewCharacterButtonTwo.OnLeftAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			DecrementCharacterClass(1);
		}
		else
		{
			mCurrentButton = &mNewCharacterButtonOne;
		}
	};
	mNewCharacterButtonTwo.OnRightAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			IncrementCharacterClass(1);
		}
	};
	mNewCharacterButtonTwo.OnDownAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER) return;

		mCurrentButton = &mNewCharacterNameButtonTwo;
	};
	mNewCharacterButtonTwo.OnAcceptAction = [this]()
	{
		if (mMenuState == EM_NEW_GAME)
		{
			mNewCharacterClassIndex = 1;
			mMenuState = EM_SELECTING_CHARACTER;
		}
		else mMenuState = EM_NEW_GAME;
	};
	mNewCharacterButtonTwo.OnCancelAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			mMenuState = EM_NEW_GAME;
			return;
		}
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
	mNewCharacterNameButtonTwo.OnAcceptAction = [this]()
	{
		mCurrentNewNameIndex = 1;
		*mNewCharacterName = "";
		mNewNamePlaceholder = *mNewCharacterNames[mCurrentNewNameIndex];

		mMenuState = EM_SELECTING_NAME;
		mCurrentButton = &mSelectLetterAButton;
		mPreviousButtonFirst = &mNewCharacterNameButtonTwo;
	};

	mNewCharacterButtonThree.OnLeftAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			DecrementCharacterClass(2);
		}
	};
	mNewCharacterButtonThree.OnRightAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			IncrementCharacterClass(2);
		}
		else
		{
			mCurrentButton = &mNewCharacterButtonFour;
		}
	};
	mNewCharacterButtonThree.OnUpAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER) return;

		mCurrentButton = &mNewCharacterNameButtonOne;
	};
	mNewCharacterButtonThree.OnDownAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER) return;

		mCurrentButton = &mNewCharacterNameButtonThree;
	};
	mNewCharacterButtonThree.OnAcceptAction = [this]()
	{
		if (mMenuState == EM_NEW_GAME)
		{
			mNewCharacterClassIndex = 2;
			mMenuState = EM_SELECTING_CHARACTER;
		}
		else mMenuState = EM_NEW_GAME;
	};
	mNewCharacterButtonThree.OnCancelAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			mMenuState = EM_NEW_GAME;
			return;
		}
	};

	mNewCharacterNameButtonThree.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonThree;
	};
	mNewCharacterNameButtonThree.OnRightAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonFour;
	};	
	mNewCharacterNameButtonThree.OnDownAction = [this]()
	{
		mCurrentButton = &mBackButton;
	};
	mNewCharacterNameButtonThree.OnAcceptAction = [this]()
	{
		mCurrentNewNameIndex = 2;
		*mNewCharacterName = "";
		mNewNamePlaceholder = *mNewCharacterNames[mCurrentNewNameIndex];

		mMenuState = EM_SELECTING_NAME;
		mCurrentButton = &mSelectLetterAButton;
		mPreviousButtonFirst = &mNewCharacterNameButtonThree;
	};

	mNewCharacterButtonFour.OnRightAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			IncrementCharacterClass(3);
		}
	};
	mNewCharacterButtonFour.OnLeftAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			DecrementCharacterClass(3);
		}
		else
		{
			mCurrentButton = &mNewCharacterButtonThree;
		}
	};
	mNewCharacterButtonFour.OnUpAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER) return;
		mCurrentButton = &mNewCharacterNameButtonTwo;
	};
	mNewCharacterButtonFour.OnDownAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER) return;

		mCurrentButton = &mNewCharacterNameButtonFour;
	};
	mNewCharacterButtonFour.OnAcceptAction = [this]()
	{
		if (mMenuState == EM_NEW_GAME)
		{
			mNewCharacterClassIndex = 3;
			mMenuState = EM_SELECTING_CHARACTER;
		}
		else mMenuState = EM_NEW_GAME;
	};
	mNewCharacterButtonFour.OnCancelAction = [this]()
	{
		if (mMenuState == EM_SELECTING_CHARACTER)
		{
			mMenuState = EM_NEW_GAME;
			return;
		}
	};

	mNewCharacterNameButtonFour.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterButtonFour;
	};
	mNewCharacterNameButtonFour.OnLeftAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonThree;
	};
	mNewCharacterNameButtonFour.OnDownAction = [this]()
	{
		mCurrentButton = &mFinishButton;
	};
	mNewCharacterNameButtonFour.OnAcceptAction = [this]()
	{
		mCurrentNewNameIndex = 3;
		*mNewCharacterName = "";
		mNewNamePlaceholder = *mNewCharacterNames[mCurrentNewNameIndex];

		mMenuState = EM_SELECTING_NAME;
		mCurrentButton = &mSelectLetterAButton;
		mPreviousButtonFirst = &mNewCharacterNameButtonFour;
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

void MenuMainMenu::SetupNewCharacterClassSprites()
{
	mNewCharacterClassOne.mSrcRect = { 0, 0, 32, 32 };
	mNewCharacterClassOne.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelOne.mPosition) + Vec2(TEXT_PADDING, 0.0f);
	mNewCharacterClassOne.mOffset = { 0.0f, -16 * TILE_SPRITE_SCALE };
	mNewCharacterClassOne.mSize = { 32 * TILE_SPRITE_SCALE, 32 * TILE_SPRITE_SCALE };
	mNewCharacterClassOne.mAssetID = mClasses[mNewCharacterClasses[0]];

	mNewCharacterClassTwo.mSrcRect = { 0, 0, 32, 32 };
	mNewCharacterClassTwo.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelTwo.mPosition) + Vec2(TEXT_PADDING, 0.0f);
	mNewCharacterClassTwo.mOffset = { 0.0f, -16 * TILE_SPRITE_SCALE };
	mNewCharacterClassTwo.mSize = { 32 * TILE_SPRITE_SCALE, 32 * TILE_SPRITE_SCALE };
	mNewCharacterClassTwo.mAssetID = mClasses[mNewCharacterClasses[1]];

	mNewCharacterClassThree.mSrcRect = { 0, 0, 32, 32 };
	mNewCharacterClassThree.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelThree.mPosition) + Vec2(TEXT_PADDING, 0.0f);
	mNewCharacterClassThree.mOffset = { 0.0f, -16 * TILE_SPRITE_SCALE };
	mNewCharacterClassThree.mSize = { 32 * TILE_SPRITE_SCALE, 32 * TILE_SPRITE_SCALE };
	mNewCharacterClassThree.mAssetID = mClasses[mNewCharacterClasses[2]];

	mNewCharacterClassFour.mSrcRect = { 0, 0, 32, 32 };
	mNewCharacterClassFour.mPosition = CalcWindowPositionFromUV(mNewCharacterPanelFour.mPosition) + Vec2(TEXT_PADDING, 0.0f);
	mNewCharacterClassFour.mOffset = { 0.0f, -16 * TILE_SPRITE_SCALE };
	mNewCharacterClassFour.mSize = { 32 * TILE_SPRITE_SCALE, 32 * TILE_SPRITE_SCALE };
	mNewCharacterClassFour.mAssetID = mClasses[mNewCharacterClasses[3]];
}

void MenuMainMenu::SetupSelectNamePanel()
{
	mSelectLetterPanel.mIsActive = true;
	mSelectLetterPanel.mPosition =
	{
		GraphicsManager::WindowWidth() * 0.5f - Font::fontWidth * TEXT_SIZE * 12.5f,
		GraphicsManager::WindowHeight() * 0.5f - Font::fontWidth * TEXT_SIZE * 2.0f
	};
	mSelectLetterPanel.mPosition = CalcWindowUVFromPosition(mSelectLetterPanel.mPosition);
	mSelectLetterPanel.mSize =
	{
		TEXT_PADDING * 2.0f + Font::fontWidth * TEXT_SIZE * 25.0f,
		TEXT_PADDING * 6.0f + Font::fontHeight * TEXT_SIZE * 5.0f
	};

	mSelectLetterEraseButton.mPosition =
	{
		GraphicsManager::WindowWidth() * 0.5f - Font::fontWidth * TEXT_SIZE * 6.0f - Font::fontSpacing * 4.0f,
		CalcWindowPositionFromUV(mSelectLetterPanel.mPosition).y + Font::fontHeight * TEXT_SIZE * 4.0f + TEXT_PADDING * 5.0f
	};
	mSelectLetterEraseButton.mText = "Erase";

	mSelectLetterEndButton.mPosition =
	{
		GraphicsManager::WindowWidth() * 0.5f + Font::fontWidth * TEXT_SIZE * 2.0f,
		CalcWindowPositionFromUV(mSelectLetterPanel.mPosition).y + Font::fontHeight * TEXT_SIZE * 4.0f + TEXT_PADDING * 5.0f
	};
	mSelectLetterEndButton.mText = "End";

	mSelectLetterPanel.mButtons.push_back(&mSelectLetterEraseButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterEndButton);

	mSelectLetterEraseButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLetterEraseButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterpButton;
	};
	mSelectLetterEraseButton.OnAcceptAction = [this]()
	{
		if (mNewCharacterName->size() == 0) return;

		mNewCharacterName->resize(mNewCharacterName->size() - 1);
	};
	mSelectLetterEraseButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};
	
	mSelectLetterEndButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLetterEndButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLettertButton;
	};
	mSelectLetterEndButton.OnAcceptAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		*mNewCharacterNames[mCurrentNewNameIndex] = *mNewCharacterName;
		SelectPreviousButtonFirst();
	};
	mSelectLetterEndButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	// Row One
	mSelectLetterAButton.mPosition = CalcWindowPositionFromUV(mSelectLetterPanel.mPosition) + Vec2(TEXT_PADDING);
	mSelectLetterAButton.mText = "A";

	mSelectLetterBButton.mPosition = mSelectLetterAButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterBButton.mText = "B";

	mSelectLetterCButton.mPosition = mSelectLetterBButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterCButton.mText = "C";

	mSelectLetterDButton.mPosition = mSelectLetterCButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterDButton.mText = "D";

	mSelectLetterEButton.mPosition = mSelectLetterDButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterEButton.mText = "E";

	mSelectLetterFButton.mPosition = mSelectLetterEButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterFButton.mText = "F";

	mSelectLetterGButton.mPosition = mSelectLetterFButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterGButton.mText = "G";

	mSelectLetterHButton.mPosition = mSelectLetterGButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterHButton.mText = "H";

	mSelectLetterIButton.mPosition = mSelectLetterHButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterIButton.mText = "I";

	mSelectLetterJButton.mPosition = mSelectLetterIButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterJButton.mText = "J";

	mSelectLetterKButton.mPosition = mSelectLetterJButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterKButton.mText = "K";

	mSelectLetterLButton.mPosition = mSelectLetterKButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterLButton.mText = "L";

	mSelectLetterMButton.mPosition = mSelectLetterLButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterMButton.mText = "M";

	// Row Two
	mSelectLetterNButton.mPosition = CalcWindowPositionFromUV(mSelectLetterPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING * 2.0f + Font::fontHeight * TEXT_SIZE);
	mSelectLetterNButton.mText = "N";

	mSelectLetterOButton.mPosition = mSelectLetterNButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterOButton.mText = "O";

	mSelectLetterPButton.mPosition = mSelectLetterOButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterPButton.mText = "P";

	mSelectLetterQButton.mPosition = mSelectLetterPButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterQButton.mText = "Q";

	mSelectLetterRButton.mPosition = mSelectLetterQButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterRButton.mText = "R";

	mSelectLetterSButton.mPosition = mSelectLetterRButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterSButton.mText = "S";

	mSelectLetterTButton.mPosition = mSelectLetterSButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterTButton.mText = "T";

	mSelectLetterUButton.mPosition = mSelectLetterTButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterUButton.mText = "U";

	mSelectLetterVButton.mPosition = mSelectLetterUButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterVButton.mText = "V";

	mSelectLetterWButton.mPosition = mSelectLetterVButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterWButton.mText = "W";

	mSelectLetterXButton.mPosition = mSelectLetterWButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterXButton.mText = "X";

	mSelectLetterYButton.mPosition = mSelectLetterXButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterYButton.mText = "Y";

	mSelectLetterZButton.mPosition = mSelectLetterYButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterZButton.mText = "Z";

	// Row Three
	mSelectLetteraButton.mPosition = CalcWindowPositionFromUV(mSelectLetterPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING * 3.0f + Font::fontHeight * TEXT_SIZE * 2.0f);
	mSelectLetteraButton.mText = "a";

	mSelectLetterbButton.mPosition = mSelectLetteraButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterbButton.mText = "b";

	mSelectLettercButton.mPosition = mSelectLetterbButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettercButton.mText = "c";

	mSelectLetterdButton.mPosition = mSelectLettercButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterdButton.mText = "d";

	mSelectLettereButton.mPosition = mSelectLetterdButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettereButton.mText = "e";

	mSelectLetterfButton.mPosition = mSelectLettereButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterfButton.mText = "f";

	mSelectLettergButton.mPosition = mSelectLetterfButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettergButton.mText = "g";

	mSelectLetterhButton.mPosition = mSelectLettergButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterhButton.mText = "h";

	mSelectLetteriButton.mPosition = mSelectLetterhButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetteriButton.mText = "i";

	mSelectLetterjButton.mPosition = mSelectLetteriButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterjButton.mText = "j";

	mSelectLetterkButton.mPosition = mSelectLetterjButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterkButton.mText = "k";

	mSelectLetterlButton.mPosition = mSelectLetterkButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterlButton.mText = "l";

	mSelectLettermButton.mPosition = mSelectLetterlButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettermButton.mText = "m";

	// Row Four
	mSelectLetternButton.mPosition = CalcWindowPositionFromUV(mSelectLetterPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING * 4.0f + Font::fontHeight * TEXT_SIZE * 3.0f);
	mSelectLetternButton.mText = "n";

	mSelectLetteroButton.mPosition = mSelectLetternButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetteroButton.mText = "o";

	mSelectLetterpButton.mPosition = mSelectLetteroButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterpButton.mText = "p";

	mSelectLetterqButton.mPosition = mSelectLetterpButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterqButton.mText = "q";

	mSelectLetterrButton.mPosition = mSelectLetterqButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterrButton.mText = "r";

	mSelectLettersButton.mPosition = mSelectLetterrButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettersButton.mText = "s";

	mSelectLettertButton.mPosition = mSelectLettersButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettertButton.mText = "t";

	mSelectLetteruButton.mPosition = mSelectLettertButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetteruButton.mText = "u";

	mSelectLettervButton.mPosition = mSelectLetteruButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLettervButton.mText = "v";

	mSelectLetterwButton.mPosition = mSelectLettervButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterwButton.mText = "w";

	mSelectLetterxButton.mPosition = mSelectLetterwButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterxButton.mText = "x";

	mSelectLetteryButton.mPosition = mSelectLetterxButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetteryButton.mText = "y";

	mSelectLetterzButton.mPosition = mSelectLetteryButton.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 2.0f, 0.0f);
	mSelectLetterzButton.mText = "z";

	// First Row
	mSelectLetterAButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterBButton;
	};
	mSelectLetterAButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterNButton;
	};
	mSelectLetterAButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('A');
	};
	mSelectLetterAButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterBButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterAButton;
	};
	mSelectLetterBButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterCButton;
	};
	mSelectLetterBButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterOButton;
	};
	mSelectLetterBButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('B');
	};
	mSelectLetterBButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterCButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterBButton;
	};
	mSelectLetterCButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterDButton;
	};
	mSelectLetterCButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterPButton;
	};
	mSelectLetterCButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('C');
	};
	mSelectLetterCButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterDButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterCButton;
	};
	mSelectLetterDButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterEButton;
	};
	mSelectLetterDButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterQButton;
	};
	mSelectLetterDButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('D');
	};
	mSelectLetterDButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterEButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterDButton;
	};
	mSelectLetterEButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterFButton;
	};
	mSelectLetterEButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterRButton;
	};
	mSelectLetterEButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('E');
	};
	mSelectLetterEButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterFButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterEButton;
	};
	mSelectLetterFButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterGButton;
	};
	mSelectLetterFButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterSButton;
	};
	mSelectLetterFButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('F');
	};
	mSelectLetterFButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterGButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterFButton;
	};
	mSelectLetterGButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterHButton;
	};
	mSelectLetterGButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterTButton;
	};
	mSelectLetterGButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('G');
	};
	mSelectLetterGButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterHButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterGButton;
	};
	mSelectLetterHButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterIButton;
	};
	mSelectLetterHButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterUButton;
	};
	mSelectLetterHButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('H');
	};
	mSelectLetterHButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterIButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterHButton;
	};
	mSelectLetterIButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterJButton;
	};
	mSelectLetterIButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterVButton;
	};
	mSelectLetterIButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('I');
	};
	mSelectLetterIButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterJButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterIButton;
	};
	mSelectLetterJButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterKButton;
	};
	mSelectLetterJButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterWButton;
	};
	mSelectLetterJButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('J');
	};
	mSelectLetterJButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterKButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterJButton;
	};
	mSelectLetterKButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterLButton;
	};
	mSelectLetterKButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterXButton;
	};
	mSelectLetterKButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('K');
	};
	mSelectLetterKButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterLButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterKButton;
	};
	mSelectLetterLButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterMButton;
	};
	mSelectLetterLButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterYButton;
	};
	mSelectLetterLButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('L');
	};
	mSelectLetterLButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterMButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterLButton;
	};
	mSelectLetterMButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterZButton;
	};
	mSelectLetterMButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('M');
	};
	mSelectLetterMButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	// Second Row
	mSelectLetterNButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterOButton;
	};
	mSelectLetterNButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterAButton;
	};
	mSelectLetterNButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetteraButton;
	};
	mSelectLetterNButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('N');
	};
	mSelectLetterNButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterOButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterNButton;
	};
	mSelectLetterOButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterPButton;
	};
	mSelectLetterOButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterBButton;
	};
	mSelectLetterOButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterbButton;
	};
	mSelectLetterOButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('O');
	};
	mSelectLetterOButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterPButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterOButton;
	};
	mSelectLetterPButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterQButton;
	};
	mSelectLetterPButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterCButton;
	};
	mSelectLetterPButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettercButton;
	};
	mSelectLetterPButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('P');
	};
	mSelectLetterPButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterQButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterPButton;
	};
	mSelectLetterQButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterRButton;
	};
	mSelectLetterQButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterDButton;
	};
	mSelectLetterQButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterdButton;
	};
	mSelectLetterQButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('Q');
	};
	mSelectLetterQButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterRButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterQButton;
	};
	mSelectLetterRButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterSButton;
	};
	mSelectLetterRButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterEButton;
	};
	mSelectLetterRButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettereButton;
	};
	mSelectLetterRButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('R');
	};
	mSelectLetterRButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterSButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterRButton;
	};
	mSelectLetterSButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterTButton;
	};
	mSelectLetterSButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterFButton;
	};
	mSelectLetterSButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterfButton;
	};
	mSelectLetterSButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('S');
	};
	mSelectLetterSButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterTButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterSButton;
	};
	mSelectLetterTButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterUButton;
	};
	mSelectLetterTButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterGButton;
	};
	mSelectLetterTButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettergButton;
	};
	mSelectLetterTButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('T');
	};
	mSelectLetterTButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterUButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterTButton;
	};
	mSelectLetterUButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterVButton;
	};
	mSelectLetterUButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterHButton;
	};
	mSelectLetterUButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterhButton;
	};
	mSelectLetterUButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('U');
	};
	mSelectLetterUButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterVButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterUButton;
	};
	mSelectLetterVButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterWButton;
	};
	mSelectLetterVButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterIButton;
	};
	mSelectLetterVButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetteriButton;
	};
	mSelectLetterVButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('V');
	};
	mSelectLetterVButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterWButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterVButton;
	};
	mSelectLetterWButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterXButton;
	};
	mSelectLetterWButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterJButton;
	};
	mSelectLetterWButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterjButton;
	};
	mSelectLetterWButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('W');
	};
	mSelectLetterWButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterXButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterWButton;
	};
	mSelectLetterXButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterYButton;
	};
	mSelectLetterXButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterKButton;
	};
	mSelectLetterXButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterkButton;
	};
	mSelectLetterXButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('X');
	};
	mSelectLetterXButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterYButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterXButton;
	};
	mSelectLetterYButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterZButton;
	};
	mSelectLetterYButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterLButton;
	};
	mSelectLetterYButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterlButton;
	};
	mSelectLetterYButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('Y');
	};
	mSelectLetterYButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterZButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterYButton;
	};
	mSelectLetterZButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterMButton;
	};
	mSelectLetterZButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettermButton;
	};
	mSelectLetterZButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('Z');
	};
	mSelectLetterZButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	// Third Row
	mSelectLetteraButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterbButton;
	};
	mSelectLetteraButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterNButton;
	};
	mSelectLetteraButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetternButton;
	};
	mSelectLetteraButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('a');
	};
	mSelectLetteraButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterbButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetteraButton;
	};
	mSelectLetterbButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettercButton;
	};
	mSelectLetterbButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterOButton;
	};
	mSelectLetterbButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetteroButton;
	};
	mSelectLetterbButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('b');
	};
	mSelectLetterbButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettercButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterbButton;
	};
	mSelectLettercButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterdButton;
	};
	mSelectLettercButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterPButton;
	};
	mSelectLettercButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterpButton;
	};
	mSelectLettercButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('c');
	};
	mSelectLettercButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterdButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLettercButton;
	};
	mSelectLetterdButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettereButton;
	};
	mSelectLetterdButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterQButton;
	};
	mSelectLetterdButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterqButton;
	};
	mSelectLetterdButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('d');
	};
	mSelectLetterdButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettereButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterdButton;
	};
	mSelectLettereButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterfButton;
	};
	mSelectLettereButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterRButton;
	};
	mSelectLettereButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterrButton;
	};
	mSelectLettereButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('e');
	};
	mSelectLettereButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterfButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLettereButton;
	};
	mSelectLetterfButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettergButton;
	};
	mSelectLetterfButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterSButton;
	};
	mSelectLetterfButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettersButton;
	};
	mSelectLetterfButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('f');
	};
	mSelectLetterfButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettergButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterfButton;
	};
	mSelectLettergButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterhButton;
	};
	mSelectLettergButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterTButton;
	};
	mSelectLettergButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettertButton;
	};
	mSelectLettergButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('g');
	};
	mSelectLettergButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterhButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLettergButton;
	};
	mSelectLetterhButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetteriButton;
	};
	mSelectLetterhButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterUButton;
	};
	mSelectLetterhButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetteruButton;
	};
	mSelectLetterhButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('h');
	};
	mSelectLetterhButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetteriButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterhButton;
	};
	mSelectLetteriButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterjButton;
	};
	mSelectLetteriButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterVButton;
	};
	mSelectLetteriButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLettervButton;
	};
	mSelectLetteriButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('i');
	};
	mSelectLetteriButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterjButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetteriButton;
	};
	mSelectLetterjButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterkButton;
	};
	mSelectLetterjButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterWButton;
	};
	mSelectLetterjButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterwButton;
	};
	mSelectLetterjButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('j');
	};
	mSelectLetterjButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterkButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterjButton;
	};
	mSelectLetterkButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterlButton;
	};
	mSelectLetterkButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterXButton;
	};
	mSelectLetterkButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterxButton;
	};
	mSelectLetterkButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('k');
	};
	mSelectLetterkButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterlButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterkButton;
	};
	mSelectLetterlButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettermButton;
	};
	mSelectLetterlButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterYButton;
	};
	mSelectLetterlButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetteryButton;
	};
	mSelectLetterlButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('l');
	};
	mSelectLetterlButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettermButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterlButton;
	};
	mSelectLettermButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterZButton;
	};
	mSelectLettermButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterzButton;
	};
	mSelectLettermButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('m');
	};
	mSelectLettermButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	// Fourth Row
	mSelectLetternButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetteroButton;
	};
	mSelectLetternButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetteraButton;
	};
	mSelectLetternButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLetternButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('n');
	};
	mSelectLetternButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetteroButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetternButton;
	};
	mSelectLetteroButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterpButton;
	};
	mSelectLetteroButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterbButton;
	};
	mSelectLetteroButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLetteroButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('o');
	};
	mSelectLetteroButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterpButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetteroButton;
	};
	mSelectLetterpButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterqButton;
	};
	mSelectLetterpButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLettercButton;
	};
	mSelectLetterpButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLetterpButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('p');
	};
	mSelectLetterpButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterqButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterpButton;
	};
	mSelectLetterqButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterrButton;
	};
	mSelectLetterqButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterdButton;
	};
	mSelectLetterqButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLetterqButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('q');
	};
	mSelectLetterqButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterrButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterqButton;
	};
	mSelectLetterrButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettersButton;
	};
	mSelectLetterrButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLettereButton;
	};
	mSelectLetterrButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLetterrButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('r');
	};
	mSelectLetterrButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettersButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterrButton;
	};
	mSelectLettersButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettertButton;
	};
	mSelectLettersButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterfButton;
	};
	mSelectLettersButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEraseButton;
	};
	mSelectLettersButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('s');
	};
	mSelectLettersButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettertButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLettersButton;
	};
	mSelectLettertButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetteruButton;
	};
	mSelectLettertButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLettergButton;
	};
	mSelectLettertButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLettertButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('t');
	};
	mSelectLettertButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetteruButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLettertButton;
	};
	mSelectLetteruButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLettervButton;
	};
	mSelectLetteruButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterhButton;
	};
	mSelectLetteruButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLetteruButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('u');
	};
	mSelectLetteruButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLettervButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetteruButton;
	};
	mSelectLettervButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterwButton;
	};
	mSelectLettervButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetteriButton;
	};
	mSelectLettervButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLettervButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('v');
	};
	mSelectLettervButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterwButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLettervButton;
	};
	mSelectLetterwButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterxButton;
	};
	mSelectLetterwButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterjButton;
	};
	mSelectLetterwButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLetterwButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('w');
	};
	mSelectLetterwButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterxButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterwButton;
	};
	mSelectLetterxButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetteryButton;
	};
	mSelectLetterxButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterkButton;
	};
	mSelectLetterxButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLetterxButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('x');
	};
	mSelectLetterxButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetteryButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetterxButton;
	};
	mSelectLetteryButton.OnRightAction = [this]()
	{
		mCurrentButton = &mSelectLetterzButton;
	};
	mSelectLetteryButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLetterlButton;
	};
	mSelectLetteryButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLetteryButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('y');
	};
	mSelectLetteryButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterzButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mSelectLetteryButton;
	};
	mSelectLetterzButton.OnUpAction = [this]()
	{
		mCurrentButton = &mSelectLettermButton;
	};
	mSelectLetterzButton.OnDownAction = [this]()
	{
		mCurrentButton = &mSelectLetterEndButton;
	};
	mSelectLetterzButton.OnAcceptAction = [this]()
	{
		AddLetterToNewName('z');
	};
	mSelectLetterzButton.OnCancelAction = [this]()
	{
		mMenuState = EM_NEW_GAME;
		SelectPreviousButtonFirst();
		ReturnNewName();
	};

	mSelectLetterPanel.mButtons.push_back(&mSelectLetterAButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterBButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterCButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterDButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterEButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterFButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterGButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterHButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterIButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterJButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterKButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterLButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterMButton);

	mSelectLetterPanel.mButtons.push_back(&mSelectLetterNButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterOButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterPButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterQButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterRButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterSButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterTButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterUButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterVButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterWButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterXButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterYButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterZButton);

	mSelectLetterPanel.mButtons.push_back(&mSelectLetteraButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterbButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettercButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterdButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettereButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterfButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettergButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterhButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetteriButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterjButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterkButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterlButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettermButton);

	mSelectLetterPanel.mButtons.push_back(&mSelectLetternButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetteroButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterpButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterqButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterrButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettersButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettertButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetteruButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLettervButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterwButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterxButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetteryButton);
	mSelectLetterPanel.mButtons.push_back(&mSelectLetterzButton);
}

void MenuMainMenu::SetupNewNamePanel()
{
	mNewNamePanel.mIsActive = true;
	mNewNamePanel.mPosition =
	{
		GraphicsManager::WindowWidth() * 0.5f - Font::fontWidth * TEXT_SIZE * 5.0f,
		CalcWindowPositionFromUV(mSelectLetterPanel.mPosition).y - Font::fontHeight * TEXT_SIZE - TEXT_PADDING * 2.0f - UI_BOX_BORDER_SIZE * 3.0f
	};
	mNewNamePanel.mPosition = CalcWindowUVFromPosition(mNewNamePanel.mPosition);
	mNewNamePanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 8.0f + Font::fontSpacing * 7.0f * TEXT_SIZE + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mNewNamePanelText.mPosition = CalcWindowPositionFromUV(mNewNamePanel.mPosition) + Vec2(TEXT_PADDING);

	mNewNamePanel.mText.push_back(&mNewNamePanelText);
}

void MenuMainMenu::SetupFinishPanel()
{
	mFinishPanel.mIsActive = true;
	mFinishPanel.mPosition =
	{
		CalcWindowPositionFromUV(mNewCharacterNamePanelFour.mPosition).x,
		GraphicsManager::WindowHeight() * 0.8f
	};
	mFinishPanel.mPosition = CalcWindowUVFromPosition(mFinishPanel.mPosition);
	mFinishPanel.mSize =
	{
		TEXT_PADDING * 2.0f + Font::fontWidth * TEXT_SIZE * 9.0f + Font::fontSpacing * TEXT_SIZE * 8.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mFinishButton.mPosition = CalcWindowPositionFromUV(mFinishPanel.mPosition) + Vec2(TEXT_PADDING);
	mFinishButton.mText = "Finish";

	mFinishButton.OnLeftAction = [this]()
	{
		mCurrentButton = &mBackButton;
	};
	mFinishButton.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonFour;
	};
	mFinishButton.OnAcceptAction = [this]()
	{
		GameManager::SetSceneToLoad("Overworld");
		GameManager::SetNewGame(true);

		for (int i = 0; i < 4; i++)
		{
			GameManager::SetNewGameClass(i, mNewCharacterClasses[i]);
			GameManager::SetNewGameNames(i, *mNewCharacterNames[i]);
		}
	};

	mFinishPanel.mButtons.push_back(&mFinishButton);

	mBackPanel.mIsActive = true;
	mBackPanel.mPosition =
	{
		CalcWindowPositionFromUV(mNewCharacterNamePanelThree.mPosition).x,
		GraphicsManager::WindowHeight() * 0.8f
	};
	mBackPanel.mPosition = CalcWindowUVFromPosition(mBackPanel.mPosition);
	mBackPanel.mSize =
	{
		TEXT_PADDING * 2.0f + Font::fontWidth * TEXT_SIZE * 9.0f + Font::fontSpacing * TEXT_SIZE * 8.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mBackButton.mPosition = CalcWindowPositionFromUV(mBackPanel.mPosition) + Vec2(TEXT_PADDING);
	mBackButton.mText = "Back";

	mBackButton.OnRightAction = [this]()
	{
		mCurrentButton = &mFinishButton;
	};
	mBackButton.OnUpAction = [this]()
	{
		mCurrentButton = &mNewCharacterNameButtonThree;
	};
	mBackButton.OnAcceptAction = [this]()
	{
		mMenuState = EM_MAIN;
		mCurrentButton = &mNewGameButton;
	};

	mBackPanel.mButtons.push_back(&mBackButton);
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

void MenuMainMenu::IncrementCharacterClass(int partyIndex)
{
	mNewCharacterClasses[partyIndex]++;
	if (mNewCharacterClasses[partyIndex] >= 4)
	{
		mNewCharacterClasses[partyIndex] = 0;
	}

	mCharacterClasses[partyIndex]->mAssetID = mClasses[mNewCharacterClasses[partyIndex]];
	mCharacterClassButtons[partyIndex]->mText = mClasses[mNewCharacterClasses[partyIndex]];
}

void MenuMainMenu::DecrementCharacterClass(int partyIndex)
{
	mNewCharacterClasses[partyIndex]--;
	if (mNewCharacterClasses[partyIndex] < 0)
	{
		mNewCharacterClasses[partyIndex] = 3;
	}

	mCharacterClasses[partyIndex]->mAssetID = mClasses[mNewCharacterClasses[partyIndex]];
	mCharacterClassButtons[partyIndex]->mText = mClasses[mNewCharacterClasses[partyIndex]];
}

void MenuMainMenu::SetNewNameText()
{
	*mNewCharacterName = "";
	*mNewCharacterNames[mCurrentNewNameIndex] = *mNewCharacterName;
}

void MenuMainMenu::AddLetterToNewName(const char character)
{
	if (mNewCharacterName->size() >= 8) return;

	*mNewCharacterName += character;
}

void MenuMainMenu::ReturnNewName()
{
	*mNewCharacterNames[mCurrentNewNameIndex] = mNewNamePlaceholder;
}