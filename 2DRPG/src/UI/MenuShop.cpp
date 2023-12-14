#include "MenuShop.h"

MenuShop::MenuShop()
{
	SetupMoneyPanel();
	SetupMainPanel();
	SetupBuyPanel();

	SetupWeaponSelectionPanel();
	SetupArmourSelectionPanel();

	SetupWeaponPurchasePromptPanel();
	SetupArmourPurchasePromptPanel();

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
	if (mWeaponPurchasePromptPanel.mIsActive)
	{
		mWeaponPurchasePromptPanel.Render();
	}
	if (mWeaponConfirmPanel.mIsActive)
	{
		mWeaponConfirmPanel.Render();
	}

	if (mArmourSelectionPanel.mIsActive)
	{
		mArmourSelectionPanel.Render();
	}
	if (mArmourPurchasePromptPanel.mIsActive)
	{
		mArmourPurchasePromptPanel.Render();
	}
	if (mArmourConfirmPanel.mIsActive)
	{
		mArmourConfirmPanel.Render();
	}
}

void MenuShop::SetupMoneyPanel()
{
	mMoneyPanel.mIsActive = true;
	int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;
	mMoneyPanel.mPosition = { 0.365f, 0.35f };
	mMoneyPanel.mSize =
	{
		stringLength + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mMoneyText.mPosition = CalcWindowPositionFromUV(mMoneyPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mMoneyText.mReference = &PlayerManager::mPartyGold;
	mMoneyText.mText = 'g';
	mMoneyPanel.mText.push_back(&mMoneyText);
}

void MenuShop::SetupMainPanel()
{
	mMainPanel.mIsActive = true;
	mMainPanel.mPosition = CalcWindowPositionFromUV(mMoneyPanel.mPosition) + Vec2(0.0f, mMoneyPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mMainPanel.mPosition = CalcWindowUVFromPosition(mMainPanel.mPosition);
	mMainPanel.mSize =
	{
		mMoneyPanel.mSize.x,
		Font::fontHeight * TEXT_SIZE * 3.0f + TEXT_PADDING * 4.0f
	};

	mMainBuyButton.mPosition = CalcWindowPositionFromUV(mMainPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
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
	mBuyMainPanel.mPosition = CalcWindowPositionFromUV(mMoneyPanel.mPosition) + Vec2(mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3.0f, 0.0f);
	mBuyMainPanel.mPosition = CalcWindowUVFromPosition(mBuyMainPanel.mPosition);
	mBuyMainPanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 30.0f + Font::fontSpacing * TEXT_SIZE * 30.0f + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mBuyMainWeaponsButton.mPosition = CalcWindowPositionFromUV(mBuyMainPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mBuyMainArmourButton.mPosition = CalcWindowPositionFromUV(mBuyMainPanel.mPosition) + Vec2(mBuyMainPanel.mSize.x * 0.33f, TEXT_PADDING);
	mBuyMainItemsButton.mPosition = CalcWindowPositionFromUV(mBuyMainPanel.mPosition) + Vec2(mBuyMainPanel.mSize.x * 0.66f, TEXT_PADDING);

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
		mCurrentButton = &mArmourSelectionButtonOne;
		mArmourSelectionPanel.mIsActive = true;
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
		//FillBuyButtonsItems();
	};

	mBuyMainPanel.mButtons.push_back(&mBuyMainWeaponsButton);
	mBuyMainPanel.mButtons.push_back(&mBuyMainArmourButton);
	mBuyMainPanel.mButtons.push_back(&mBuyMainItemsButton);
}

void MenuShop::SetupWeaponSelectionPanel()
{
	mWeaponSelectionPanel.mIsActive = false;
	mWeaponSelectionPanel.mPosition = CalcWindowPositionFromUV(mBuyMainPanel.mPosition) + Vec2(0.0f, mBuyMainPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mWeaponSelectionPanel.mPosition = CalcWindowUVFromPosition(mWeaponSelectionPanel.mPosition);
	mWeaponSelectionPanel.mSize =
	{
		mBuyMainPanel.mSize.x,
		TEXT_PADDING + (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 5.0f
	};

	mWeaponSelectionButtonOne.mPosition = CalcWindowPositionFromUV(mWeaponSelectionPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
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
		mWeaponPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetWeaponPromptText();
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
		mWeaponPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetWeaponPromptText();
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
		mWeaponPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetWeaponPromptText();
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
		mWeaponPurchasePromptPanel.mIsActive = true;
		mWeaponConfirmPanel.mIsActive = true;
		SetWeaponPromptText();
	};

	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonOne);
	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonTwo);
	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonThree);
	mWeaponSelectionPanel.mButtons.push_back(&mWeaponSelectionButtonFour);

	mWeaponPriceTextOne.mPosition = mWeaponSelectionButtonOne.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mWeaponPriceTextTwo.mPosition = mWeaponSelectionButtonTwo.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mWeaponPriceTextThree.mPosition = mWeaponSelectionButtonThree.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mWeaponPriceTextFour.mPosition = mWeaponSelectionButtonFour.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);

	mWeaponSelectionPanel.mText.push_back(&mWeaponPriceTextOne);
	mWeaponSelectionPanel.mText.push_back(&mWeaponPriceTextTwo);
	mWeaponSelectionPanel.mText.push_back(&mWeaponPriceTextThree);
	mWeaponSelectionPanel.mText.push_back(&mWeaponPriceTextFour);
}

void MenuShop::SetupArmourSelectionPanel()
{
	mArmourSelectionPanel.mIsActive = false;
	mArmourSelectionPanel.mPosition = CalcWindowPositionFromUV(mBuyMainPanel.mPosition) + Vec2(0.0f, mBuyMainPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mArmourSelectionPanel.mPosition = CalcWindowUVFromPosition(mArmourSelectionPanel.mPosition);
	mArmourSelectionPanel.mSize =
	{
		mBuyMainPanel.mSize.x,
		TEXT_PADDING + (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 5.0f
	};

	mArmourSelectionButtonOne.mPosition = CalcWindowPositionFromUV(mArmourSelectionPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mArmourSelectionButtonTwo.mPosition = mArmourSelectionButtonOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mArmourSelectionButtonThree.mPosition = mArmourSelectionButtonTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mArmourSelectionButtonFour.mPosition = mArmourSelectionButtonThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	mArmourSelectionButtonOne.mText = "One";
	mArmourSelectionButtonTwo.mText = "Two";
	mArmourSelectionButtonThree.mText = "Three";
	mArmourSelectionButtonFour.mText = "Four";

	mArmourSelectionButtonOne.OnDownAction = [this]()
	{
		if (mArmourSelectionButtonTwo.mIsActive) mCurrentButton = &mArmourSelectionButtonTwo;
	};
	mArmourSelectionButtonOne.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mArmourSelectionPanel.mIsActive = false;
	};
	mArmourSelectionButtonOne.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mArmourSelectionButtonOne;
		mSelectedArmourIndex = 0;
		mCurrentButton = &mArmourConfirmButtonYes;
		mArmourPurchasePromptPanel.mIsActive = true;
		mArmourConfirmPanel.mIsActive = true;
		SetArmourPromptText();
	};

	mArmourSelectionButtonTwo.OnUpAction = [this]()
	{
		if (mArmourSelectionButtonOne.mIsActive) mCurrentButton = &mArmourSelectionButtonOne;
	};
	mArmourSelectionButtonTwo.OnDownAction = [this]()
	{
		if (mArmourSelectionButtonThree.mIsActive) mCurrentButton = &mArmourSelectionButtonThree;
	};
	mArmourSelectionButtonTwo.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mArmourSelectionPanel.mIsActive = false;
	};
	mArmourSelectionButtonTwo.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mArmourSelectionButtonTwo;
		mSelectedArmourIndex = 1;
		mCurrentButton = &mArmourConfirmButtonYes;
		mArmourPurchasePromptPanel.mIsActive = true;
		mArmourConfirmPanel.mIsActive = true;
		SetArmourPromptText();
	};

	mArmourSelectionButtonThree.OnUpAction = [this]()
	{
		if (mArmourSelectionButtonTwo.mIsActive) mCurrentButton = &mArmourSelectionButtonTwo;
	};
	mArmourSelectionButtonThree.OnDownAction = [this]()
	{
		if (mArmourSelectionButtonFour.mIsActive) mCurrentButton = &mArmourSelectionButtonFour;
	};
	mArmourSelectionButtonThree.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mArmourSelectionPanel.mIsActive = false;
	};
	mArmourSelectionButtonThree.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mArmourSelectionButtonThree;
		mSelectedArmourIndex = 2;
		mCurrentButton = &mArmourConfirmButtonYes;
		mArmourPurchasePromptPanel.mIsActive = true;
		mArmourConfirmPanel.mIsActive = true;
		SetArmourPromptText();
	};

	mArmourSelectionButtonFour.OnUpAction = [this]()
	{
		if (mArmourSelectionButtonThree.mIsActive) mCurrentButton = &mArmourSelectionButtonThree;
	};
	mArmourSelectionButtonFour.OnCancelAction = [this]()
	{
		SelectPreviousButtonFirst();
		mArmourSelectionPanel.mIsActive = false;
	};
	mArmourSelectionButtonFour.OnAcceptAction = [this]()
	{
		mPreviousButtonSecond = &mArmourSelectionButtonOne;
		mSelectedArmourIndex = 3;
		mCurrentButton = &mArmourConfirmButtonYes;
		mArmourPurchasePromptPanel.mIsActive = true;
		mArmourConfirmPanel.mIsActive = true;
		SetArmourPromptText();
	};

	mArmourSelectionPanel.mButtons.push_back(&mArmourSelectionButtonOne);
	mArmourSelectionPanel.mButtons.push_back(&mArmourSelectionButtonTwo);
	mArmourSelectionPanel.mButtons.push_back(&mArmourSelectionButtonThree);
	mArmourSelectionPanel.mButtons.push_back(&mArmourSelectionButtonFour);

	mArmourPriceTextOne.mPosition = mArmourSelectionButtonOne.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mArmourPriceTextTwo.mPosition = mArmourSelectionButtonTwo.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mArmourPriceTextThree.mPosition = mArmourSelectionButtonThree.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);
	mArmourPriceTextFour.mPosition = mArmourSelectionButtonFour.mPosition + Vec2(Font::fontWidth * TEXT_SIZE * 10.0f, 0.0f);

	mArmourSelectionPanel.mText.push_back(&mArmourPriceTextOne);
	mArmourSelectionPanel.mText.push_back(&mArmourPriceTextTwo);
	mArmourSelectionPanel.mText.push_back(&mArmourPriceTextThree);
	mArmourSelectionPanel.mText.push_back(&mArmourPriceTextFour);
}

void MenuShop::SetupWeaponPurchasePromptPanel()
{
	mWeaponPurchasePromptPanel.mIsActive = false;
	mWeaponPurchasePromptPanel.mPosition = CalcWindowPositionFromUV(mWeaponSelectionPanel.mPosition) + Vec2(0.0f, mWeaponSelectionPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mWeaponPurchasePromptPanel.mPosition = CalcWindowUVFromPosition(mWeaponPurchasePromptPanel.mPosition);
	mWeaponPurchasePromptPanel.mSize =
	{
		mWeaponSelectionPanel.mSize.x,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mWeaponPurchasePromptText.mPosition = CalcWindowPositionFromUV(mWeaponPurchasePromptPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mWeaponPurchasePromptPanel.mText.push_back(&mWeaponPurchasePromptText);

	mWeaponConfirmPanel.mIsActive = false;
	mWeaponConfirmPanel.mPosition =
		CalcWindowPositionFromUV(mWeaponPurchasePromptPanel.mPosition) + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f + UI_BOX_BORDER_SIZE * 3.0f);
	mWeaponConfirmPanel.mPosition = CalcWindowUVFromPosition(mWeaponConfirmPanel.mPosition);
	mWeaponConfirmPanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 5.0f + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE * 2.0f + TEXT_PADDING * 3.0f
	};

	mWeaponConfirmButtonYes.mPosition = CalcWindowPositionFromUV(mWeaponConfirmPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
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
			mWeaponPurchasePromptPanel.mIsActive = false;
			mWeaponConfirmPanel.mIsActive = false;
		}
		else
		{
			mWeaponPurchasePromptText.mText = "You can't afford that.";
		}
	};
	mWeaponConfirmButtonYes.OnCancelAction = [this]()
	{
		SelectPreviousButtonSecond();
		mWeaponPurchasePromptPanel.mIsActive = false;
		mWeaponConfirmPanel.mIsActive = false;
	};

	mWeaponConfirmButtonNo.OnUpAction = [this]()
	{
		mCurrentButton = &mWeaponConfirmButtonYes;
	};
	mWeaponConfirmButtonNo.OnAcceptAction = [this]()
	{
		SelectPreviousButtonSecond();
		mWeaponPurchasePromptPanel.mIsActive = false;
		mWeaponConfirmPanel.mIsActive = false;
	};
	mWeaponConfirmButtonNo.OnCancelAction = [this]()
	{
		SelectPreviousButtonSecond();
		mWeaponPurchasePromptPanel.mIsActive = false;
		mWeaponConfirmPanel.mIsActive = false;
	};

	mWeaponConfirmPanel.mButtons.push_back(&mWeaponConfirmButtonYes);
	mWeaponConfirmPanel.mButtons.push_back(&mWeaponConfirmButtonNo);
}

void MenuShop::SetupArmourPurchasePromptPanel()
{
	mArmourPurchasePromptPanel.mIsActive = false;
	mArmourPurchasePromptPanel.mPosition = CalcWindowPositionFromUV(mArmourSelectionPanel.mPosition) + Vec2(0.0f, mArmourSelectionPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f);
	mArmourPurchasePromptPanel.mPosition = CalcWindowUVFromPosition(mArmourPurchasePromptPanel.mPosition);
	mArmourPurchasePromptPanel.mSize =
	{
		mArmourSelectionPanel.mSize.x,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
	};

	mArmourPurchasePromptText.mPosition = CalcWindowPositionFromUV(mArmourPurchasePromptPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mArmourPurchasePromptPanel.mText.push_back(&mArmourPurchasePromptText);

	mArmourConfirmPanel.mIsActive = false;
	mArmourConfirmPanel.mPosition =
		CalcWindowPositionFromUV(mArmourPurchasePromptPanel.mPosition) + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f + UI_BOX_BORDER_SIZE * 3.0f);
	mArmourConfirmPanel.mPosition = CalcWindowUVFromPosition(mArmourConfirmPanel.mPosition);
	mArmourConfirmPanel.mSize =
	{
		Font::fontWidth * TEXT_SIZE * 5.0f + TEXT_PADDING * 2.0f,
		Font::fontHeight * TEXT_SIZE * 2.0f + TEXT_PADDING * 3.0f
	};

	mArmourConfirmButtonYes.mPosition = CalcWindowPositionFromUV(mArmourConfirmPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mArmourConfirmButtonYes.mText = "Yes";

	mArmourConfirmButtonNo.mPosition = mArmourConfirmButtonYes.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mArmourConfirmButtonNo.mText = "No";

	mArmourConfirmButtonYes.OnDownAction = [this]()
	{
		mCurrentButton = &mArmourConfirmButtonNo;
	};
	mArmourConfirmButtonYes.OnAcceptAction = [this]()
	{
		if (PurchaseArmour())
		{
			SelectPreviousButtonSecond();
			mArmourPurchasePromptPanel.mIsActive = false;
			mArmourConfirmPanel.mIsActive = false;
		}
		else
		{
			mArmourPurchasePromptText.mText = "You can't afford that.";
		}
	};
	mArmourConfirmButtonYes.OnCancelAction = [this]()
	{
		SelectPreviousButtonSecond();
		mArmourPurchasePromptPanel.mIsActive = false;
		mArmourConfirmPanel.mIsActive = false;
	};

	mArmourConfirmButtonNo.OnUpAction = [this]()
	{
		mCurrentButton = &mArmourConfirmButtonYes;
	};
	mArmourConfirmButtonNo.OnAcceptAction = [this]()
	{
		SelectPreviousButtonSecond();
		mArmourPurchasePromptPanel.mIsActive = false;
		mArmourConfirmPanel.mIsActive = false;
	};
	mArmourConfirmButtonNo.OnCancelAction = [this]()
	{
		SelectPreviousButtonSecond();
		mArmourPurchasePromptPanel.mIsActive = false;
		mArmourConfirmPanel.mIsActive = false;
	};

	mArmourConfirmPanel.mButtons.push_back(&mArmourConfirmButtonYes);
	mArmourConfirmPanel.mButtons.push_back(&mArmourConfirmButtonNo);
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
		mWeaponSelectionPanel.mText[i]->mText = std::to_string(mWeapons[i].mBuyCost) + 'g';
	}
}

void MenuShop::FillBuyButtonsArmour()
{
	mArmourSelectionButtonOne.mIsActive = false;
	mArmourSelectionButtonTwo.mIsActive = false;
	mArmourSelectionButtonThree.mIsActive = false;
	mArmourSelectionButtonFour.mIsActive = false;

	for (int i = 0; i < mArmour.size(); i++)
	{
		mArmourSelectionPanel.mButtons[i]->mIsActive = true;
		mArmourSelectionPanel.mButtons[i]->mText = mArmour[i].mName;
		mArmourSelectionPanel.mText[i]->mText = std::to_string(mArmour[i].mBuyCost) + 'g';
	}
}

void MenuShop::FillBuyButtonsItems()
{
	mWeaponSelectionButtonOne.mIsActive = false;
	mWeaponSelectionButtonTwo.mIsActive = false;
	mWeaponSelectionButtonThree.mIsActive = false;
	mWeaponSelectionButtonFour.mIsActive = false;
}

void MenuShop::SetWeaponPromptText()
{
	mWeaponPurchasePromptText.mText =
		"Purchase " +
		mWeapons[mSelectedWeaponIndex].mName +
		" for " +
		std::to_string(mWeapons[mSelectedWeaponIndex].mBuyCost) +
		"g?";
}

void MenuShop::SetArmourPromptText()
{
	mArmourPurchasePromptText.mText =
		"Purchase " +
		mArmour[mSelectedArmourIndex].mName +
		" for " +
		std::to_string(mArmour[mSelectedArmourIndex].mBuyCost) +
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

bool MenuShop::PurchaseArmour()
{
	if (PlayerManager::GetPartyGold() >= mArmour[mSelectedArmourIndex].mBuyCost)
	{
		switch (mArmour[mSelectedArmourIndex].mArmourType)
		{
			case Armour::HEAD:
			{
				PlayerManager::AddArmourHeadToInventory(mArmour[mSelectedArmourIndex]);
				break;
			}
			case Armour::BODY:
			{
				PlayerManager::AddArmourBodyToInventory(mArmour[mSelectedArmourIndex]);
				break;
			}
		}
		PlayerManager::SubtractGold(mArmour[mSelectedArmourIndex].mBuyCost);
		return true;
	}

	return false;
}