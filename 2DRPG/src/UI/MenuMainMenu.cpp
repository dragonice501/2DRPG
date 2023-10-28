#include "MenuMainMenu.h"

MenuMainMenu::MenuMainMenu()
{
	SetupNewGamePanel();
	SetupContinuePanel();
	SetupQuitPanel();

	mCurrentButton = &mNewGameButton;
}

void MenuMainMenu::Render()
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

	mNewGamePanel.mButtons.push_back(&mNewGameButton);
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

	mQuitPanel.mButtons.push_back(&mQuitButton);
}
