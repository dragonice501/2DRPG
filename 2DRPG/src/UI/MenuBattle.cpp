#include "MenuBattle.h"

MenuBattle::MenuBattle() :
	mFightButton("Fight"), mMagicButton("Magic"), mItemButton("Item"), mRunButton("Run")
{
	mPartyActionPanel.mIsActive = true;
	mPartyActionPanel.mPosition =
	{
		GraphicsManager::WindowWidth() / 2.0f + 100.0f,
		GraphicsManager::WindowHeight() - BATTLE_MENU_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2.0f
	};
	mPartyActionPanel.mSize =
	{ 
		BATTLE_MENU_WIDTH,
		BATTLE_MENU_HEIGHT
	};
	mPartyActionPanel.mButtons.push_back(&mFightButton);
	mPartyActionPanel.mButtons.push_back(&mMagicButton);
	mPartyActionPanel.mButtons.push_back(&mItemButton);
	mPartyActionPanel.mButtons.push_back(&mRunButton);

	mFightButton.mPosition = { mPartyActionPanel.mPosition.x + TEXT_PADDING, mPartyActionPanel.mPosition.y + TEXT_PADDING };
	mMagicButton.mPosition = { mPartyActionPanel.mPosition.x + TEXT_PADDING, mPartyActionPanel.mPosition.y + TEXT_PADDING + 30 };
	mItemButton.mPosition = { mPartyActionPanel.mPosition.x + TEXT_PADDING, mPartyActionPanel.mPosition.y + TEXT_PADDING + 60 };
	mRunButton.mPosition = { mPartyActionPanel.mPosition.x + TEXT_PADDING, mPartyActionPanel.mPosition.y + TEXT_PADDING + 90 };

	for (int i = 0; i < 6; i++)
		mSmallEnemyButtons.push_back(UIButton());
}

void MenuBattle::Render(SDL_Renderer* renderer)
{
	if (mPartyActionPanel.mIsActive)
	{
		mPartyActionPanel.Render();
	}

	if (mCurrentButton)
	{
		GraphicsManager::DrawUISelector(
			mCurrentButton->mPosition.x - TEXT_PADDING / 2,
			mCurrentButton->mPosition.y - TEXT_PADDING / 2,
			Font::GetStringFontLength(mCurrentButton->mText.c_str()) * TEXT_SIZE + TEXT_PADDING,
			Font::fontHeight * TEXT_SIZE + TEXT_PADDING
		);
	}
}