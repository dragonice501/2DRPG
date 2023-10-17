#include "MenuShop.h"

MenuShop::MenuShop()
{
	SetupMainPanel();

	mCurrentButton = &mMainBuyButton;
}

void MenuShop::Render()
{
	if (mMainPanel.mIsActive)
	{
		mMainPanel.Render();
	}
}

void MenuShop::SetupMainPanel()
{
	mMainPanel.mIsActive = true;
	mMainPanel.mPosition =
	{
		GraphicsManager::WindowWidth() / 2.0f,
		GraphicsManager::WindowHeight() / 2.0f
	};
	mMainPanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 9.0f + Font::fontSpacing * TEXT_SIZE * 9.0f,
		Font::fontHeight * TEXT_SIZE * 3.0f + TEXT_PADDING * 4.0f
	};

	mMainBuyButton.mPosition = mMainPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
	mMainSellButton.mPosition = mMainBuyButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mMainExitButton.mPosition = mMainSellButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	mMainBuyButton.mText = "Buy";
	mMainSellButton.mText = "Sell";
	mMainExitButton.mText = "Exit";

	mMainBuyButton.OnDownAction = [this]()
	{
		mCurrentButton = &mMainSellButton;
	};

	mMainSellButton.OnUpAction = [this]()
	{
		mCurrentButton = &mMainBuyButton;
	};
	mMainSellButton.OnDownAction = [this]()
	{
		mCurrentButton = &mMainExitButton;
	};

	mMainExitButton.OnUpAction = [this]()
	{
		mCurrentButton = &mMainSellButton;
	};

	mMainPanel.mButtons.push_back(&mMainBuyButton);
	mMainPanel.mButtons.push_back(&mMainSellButton);
	mMainPanel.mButtons.push_back(&mMainExitButton);
}