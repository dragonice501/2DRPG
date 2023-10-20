#include "MenuShop.h"

MenuShop::MenuShop()
{
	SetupMoneyPanel();
	SetupMainPanel();
	SetupBuyPanel();
	SetupWeaponSelectionPanel();
	SetupPurchasePromptPanel();

	mCurrentButton = &mMainBuyButton;
}

void MenuShop::Render()
{
	if (mMoneyPanel.mIsActive)
	{
		mMoneyPanel.Render();
	}

	if (mMainPanel.mIsActive)
	{
		mMainPanel.Render();
	}

	if (mBuyMainPanel.mIsActive)
	{
		mBuyMainPanel.Render();
	}

	if (mWeaponSelectionPanel.mIsActive)
	{
		mWeaponSelectionPanel.Render();
	}

	if (mPurchasePromptPanel.mIsActive)
	{
		mPurchasePromptPanel.Render();
	}

	if (mWeaponConfirmPanel.mIsActive)
	{
		mWeaponConfirmPanel.Render();
	}
}

void MenuShop::SetupMoneyPanel()
{
	mMoneyPanel.mIsActive = true;
	int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;
	mMoneyPanel.mPosition =
	{
		GraphicsManager::WindowWidth() / 2.0f - GraphicsManager::WindowWidth() / 4.0f,
		GraphicsManager::WindowHeight() / 2.0f - GraphicsManager::WindowHeight() / 4.0f
	};
	mMoneyPanel.mSize =
	{
		stringLength + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mMoneyText.mPosition =
	{
		mMoneyPanel.mPosition.x + TEXT_PADDING,
		mMoneyPanel.mPosition.y + TEXT_PADDING
	};
	mMoneyText.mReference = &PlayerManager::mPartyGold;
	mMoneyText.mText = 'g';
	mMoneyPanel.mText.push_back(mMoneyText);
}

void MenuShop::SetupMainPanel()
{
	mMainPanel.mIsActive = true;
	mMainPanel.mPosition = mMoneyPanel.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f + UI_BOX_BORDER_SIZE * 3.0f);
	mMainPanel.mSize =
	{
		mMoneyPanel.mSize.x,
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
	mMainBuyButton.OnAcceptAction = [this]()
	{
		mCurrentButton = &mBuyMainWeaponsButton;
		mBuyMainPanel.mIsActive = true;
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

void MenuShop::SetupBuyPanel()
{
	mBuyMainPanel.mIsActive = false;
	mBuyMainPanel.mPosition = mMoneyPanel.mPosition + Vec2(mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3.0f, 0.0f);
	mBuyMainPanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 30.0f + Font::fontSpacing * TEXT_SIZE * 30.0f + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mBuyMainWeaponsButton.mPosition =
	{
		mBuyMainPanel.mPosition.x + TEXT_PADDING,
		mBuyMainPanel.mPosition.y + TEXT_PADDING
	};
	mBuyMainArmourButton.mPosition =
	{
		mBuyMainPanel.mPosition.x + mBuyMainPanel.mSize.x * 0.33f,
		mBuyMainPanel.mPosition.y + TEXT_PADDING
	};
	mBuyMainItemsButton.mPosition =
	{
		mBuyMainPanel.mPosition.x + mBuyMainPanel.mSize.x * 0.66f,
		mBuyMainPanel.mPosition.y + TEXT_PADDING
	};

	mBuyMainWeaponsButton.mText = "Weapons";
	mBuyMainArmourButton.mText = "Armour";
	mBuyMainItemsButton.mText = "Items";

	mBuyMainWeaponsButton.OnRightAction = [this]()
	{
		mCurrentButton = &mBuyMainArmourButton;
	};
	mBuyMainWeaponsButton.OnCancelAction = [this]()
	{
		mCurrentButton = &mMainBuyButton;
		mBuyMainPanel.mIsActive = false;
	};
	mBuyMainWeaponsButton.OnAcceptAction = [this]()
	{
		mPreviousButtonFirst = &mBuyMainWeaponsButton;
		mCurrentButton = &mWeaponSelectionButtonOne;
		mWeaponSelectionPanel.mIsActive = true;
		FillBuyButtonsWeapons();
	};

	mBuyMainArmourButton.OnRightAction = [this]
	{
		mCurrentButton = &mBuyMainItemsButton;
	};
	mBuyMainArmourButton.OnLeftAction = [this]
	{
		mCurrentButton = &mBuyMainWeaponsButton;
	};
	mBuyMainArmourButton.OnCancelAction = [this]()
	{
		mCurrentButton = &mMainBuyButton;
		mBuyMainPanel.mIsActive = false;
	};
	mBuyMainArmourButton.OnAcceptAction = [this]()
	{
		mPreviousButtonFirst = &mBuyMainArmourButton;
		mCurrentButton = &mWeaponSelectionButtonOne;
		mWeaponSelectionPanel.mIsActive = true;
		FillBuyButtonsArmour();
	};

	mBuyMainItemsButton.OnLeftAction = [this]
	{
		mCurrentButton = &mBuyMainArmourButton;
	};
	mBuyMainItemsButton.OnCancelAction = [this]()
	{
		mCurrentButton = &mMainBuyButton;
		mBuyMainPanel.mIsActive = false;
	};
	mBuyMainItemsButton.OnAcceptAction = [this]()
	{
		mPreviousButtonFirst = &mBuyMainItemsButton;
		mCurrentButton = &mWeaponSelectionButtonOne;
		mWeaponSelectionPanel.mIsActive = true;
		FillBuyButtonsItems();
	};

	mBuyMainPanel.mButtons.push_back(&mBuyMainWeaponsButton);
	mBuyMainPanel.mButtons.push_back(&mBuyMainArmourButton);
	mBuyMainPanel.mButtons.push_back(&mBuyMainItemsButton);
}

void MenuShop::SetupWeaponSelectionPanel()
{
	mWeaponSelectionPanel.mIsActive = false;
	mWeaponSelectionPanel.mPosition =
	{
		mBuyMainPanel.mPosition.x,
		mBuyMainPanel.mPosition.y + Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f + UI_BOX_BORDER_SIZE * 3.0f
	};
	mWeaponSelectionPanel.mSize =
	{
		mBuyMainPanel.mSize.x,
		TEXT_PADDING + (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 5.0f
	};

	mWeaponSelectionButtonOne.mPosition = mWeaponSelectionPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
	mWeaponSelectionButtonTwo.mPosition = mWeaponSelectionButtonOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mWeaponSelectionButtonThree.mPosition = mWeaponSelectionButtonTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mWeaponSelectionButtonFour.mPosition = mWeaponSelectionButtonThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	mWeaponSelectionButtonOne.mText = "One";
	mWeaponSelectionButtonTwo.mText = "Two";
	mWeaponSelectionButtonThree.mText = "Three";
	mWeaponSelectionButtonFour.mText = "Four";

	mWeaponSelectionButtonOne.OnDownAction = [this]()
	{
		if(mWeaponSelectionButtonTwo.mIsActive) mCurrentButton = &mWeaponSelectionButtonTwo;
	};
	mWeaponSelectionButtonOne.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mWeaponSelectionPanel.mIsActive = false;
	};
	mWeaponSelectionButtonOne.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mWeaponSelectionButtonOne;
		mSelectedWeaponIndex = 0;
		mCurrentButton = &mWeaponConfirmButtonYes;
		mPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetPromptText();
	};

	mWeaponSelectionButtonTwo.OnUpAction = [this]()
	{
		if (mWeaponSelectionButtonOne.mIsActive) mCurrentButton = &mWeaponSelectionButtonOne;
	};
	mWeaponSelectionButtonTwo.OnDownAction = [this]()
	{
		if (mWeaponSelectionButtonThree.mIsActive) mCurrentButton = &mWeaponSelectionButtonThree;
	};
	mWeaponSelectionButtonTwo.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mWeaponSelectionPanel.mIsActive = false;
	};
	mWeaponSelectionButtonTwo.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mWeaponSelectionButtonTwo;
		mSelectedWeaponIndex = 1;
		mCurrentButton = &mWeaponConfirmButtonYes;
		mPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetPromptText();
	};

	mWeaponSelectionButtonThree.OnUpAction = [this]()
	{
		if (mWeaponSelectionButtonTwo.mIsActive) mCurrentButton = &mWeaponSelectionButtonTwo;
	};
	mWeaponSelectionButtonThree.OnDownAction = [this]()
	{
		if (mWeaponSelectionButtonFour.mIsActive) mCurrentButton = &mWeaponSelectionButtonFour;
	};
	mWeaponSelectionButtonThree.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mWeaponSelectionPanel.mIsActive = false;
	};
	mWeaponSelectionButtonThree.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mWeaponSelectionButtonThree;
		mSelectedWeaponIndex = 2;
		mCurrentButton = &mWeaponConfirmButtonYes;
		mPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetPromptText();
	};

	mWeaponSelectionButtonFour.OnUpAction = [this]()
	{
		if (mWeaponSelectionButtonThree.mIsActive) mCurrentButton = &mWeaponSelectionButtonThree;
	};
	mWeaponSelectionButtonFour.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mWeaponSelectionPanel.mIsActive = false;
	};
	mWeaponSelectionButtonFour.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mWeaponSelectionButtonOne;
		mSelectedWeaponIndex = 3;
		mCurrentButton = &mWeaponConfirmButtonYes;
		mPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetPromptText();
	};

	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonOne);
	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonTwo);
	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonThree);
	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonFour);

	mWeaponPriceTextOne.mPosition = mWeaponSelectionButtonOne.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mWeaponPriceTextTwo.mPosition = mWeaponSelectionButtonTwo.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mWeaponPriceTextThree.mPosition = mWeaponSelectionButtonThree.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mWeaponPriceTextFour.mPosition = mWeaponSelectionButtonFour.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);

	mWeaponSelectionPanel.mText.push_back(mWeaponPriceTextOne);
	mWeaponSelectionPanel.mText.push_back(mWeaponPriceTextTwo);
	mWeaponSelectionPanel.mText.push_back(mWeaponPriceTextThree);
	mWeaponSelectionPanel.mText.push_back(mWeaponPriceTextFour);
}

void MenuShop::SetupPurchasePromptPanel()
{
	mPurchasePromptPanel.mIsActive = false;
	mPurchasePromptPanel.mPosition = mWeaponSelectionPanel.mPosition + Vec2(0.0f, mWeaponSelectionPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mPurchasePromptPanel.mSize =
	{
		mWeaponSelectionPanel.mSize.x,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mPurchasePromptText.mPosition = mPurchasePromptPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
	mPurchasePromptPanel.mText.push_back(mPurchasePromptText);

	mWeaponConfirmPanel.mIsActive = false;
	mWeaponConfirmPanel.mPosition = mPurchasePromptPanel.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f + UI_BOX_BORDER_SIZE * 3.0f);
	mWeaponConfirmPanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 5.0f + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE * 2.0f + TEXT_PADDING * 3.0f
	};

	mWeaponConfirmButtonYes.mPosition = mWeaponConfirmPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
	mWeaponConfirmButtonYes.mText = "Yes";

	mWeaponConfirmButtonNo.mPosition = mWeaponConfirmButtonYes.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mWeaponConfirmButtonNo.mText = "No";

	mWeaponConfirmButtonYes.OnDownAction = [this]()
	{
		mCurrentButton = &mWeaponConfirmButtonNo;
	};
	mWeaponConfirmButtonYes.OnAcceptAction = [this]()
	{
		if (PurchaseWeapon())
		{
			SelectPreviousButtonSecond();
			mPurchasePromptPanel.mIsActive = false;
			mWeaponConfirmPanel.mIsActive = false;
		}
		else
		{
			mPurchasePromptPanel.mText[0].mText = "You can't afford that.";
		}
	};
	mWeaponConfirmButtonYes.OnCancelAction = [this]()
	{
		SelectPreviousButtonSecond();
		mPurchasePromptPanel.mIsActive = false;
		mWeaponConfirmPanel.mIsActive = false;
	};

	mWeaponConfirmButtonNo.OnUpAction = [this]()
	{
		mCurrentButton = &mWeaponConfirmButtonYes;
	};
	mWeaponConfirmButtonNo.OnAcceptAction = [this]()
	{
		SelectPreviousButtonSecond();
		mPurchasePromptPanel.mIsActive = false;
		mWeaponConfirmPanel.mIsActive = false;
	};
	mWeaponConfirmButtonNo.OnCancelAction = [this]()
	{
		SelectPreviousButtonSecond();
		mPurchasePromptPanel.mIsActive = false;
		mWeaponConfirmPanel.mIsActive = false;
	};

	mWeaponConfirmPanel.mButtons.push_back(&mWeaponConfirmButtonYes);
	mWeaponConfirmPanel.mButtons.push_back(&mWeaponConfirmButtonNo);
}

void MenuShop::FillBuyButtonsWeapons()
{
	mWeaponSelectionButtonOne.mIsActive = false;
	mWeaponSelectionButtonTwo.mIsActive = false;
	mWeaponSelectionButtonThree.mIsActive = false;
	mWeaponSelectionButtonFour.mIsActive = false;

	for (int i = 0; i < mWeapons.size(); i++)
	{
		mWeaponSelectionPanel.mButtons[i]->mIsActive = true;
		mWeaponSelectionPanel.mButtons[i]->mText = mWeapons[i].mName;
		mWeaponSelectionPanel.mText[i].mText = std::to_string(mWeapons[i].mBuyCost) + 'g';
	}
}

void MenuShop::FillBuyButtonsArmour()
{
	mWeaponSelectionButtonOne.mIsActive = false;
	mWeaponSelectionButtonTwo.mIsActive = false;
	mWeaponSelectionButtonThree.mIsActive = false;
	mWeaponSelectionButtonFour.mIsActive = false;
}

void MenuShop::FillBuyButtonsItems()
{
	mWeaponSelectionButtonOne.mIsActive = false;
	mWeaponSelectionButtonTwo.mIsActive = false;
	mWeaponSelectionButtonThree.mIsActive = false;
	mWeaponSelectionButtonFour.mIsActive = false;
}

void MenuShop::SetPromptText()
{
	mPurchasePromptPanel.mText[0].mText =
		"Purchase " +
		mWeapons[mSelectedWeaponIndex].mName +
		" for " +
		std::to_string(mWeapons[mSelectedWeaponIndex].mBuyCost) +
		"g?";
}

bool MenuShop::PurchaseWeapon()
{
	if (PlayerManager::GetPartyGold() >= mWeapons[mSelectedWeaponIndex].mBuyCost)
	{
		PlayerManager::AddWeaponToInventory(mWeapons[mSelectedWeaponIndex]);
		PlayerManager::SubtractGold(mWeapons[mSelectedWeaponIndex].mBuyCost);
		return true;
	}

	return false;
}
