#pragma once

#include "Menu.h"

#include "../Items/Weapon.h"

#include "../Managers/PlayerManager.h"

#include <vector>

class MenuShop : public Menu
{
private:
	enum EShoppingState
	{
		SS_MAIN,
		SS_BUYING,
		SS_SELLING
	};

public:
	MenuShop();

	void Render() override;

	void SetupMoneyPanel();
	void SetupMainPanel();
	void SetupBuyPanel();
	void SetupWeaponSelectionPanel();
	void SetupPurchasePromptPanel();

	void FillBuyButtonsWeapons();
	void FillBuyButtonsArmour();
	void FillBuyButtonsItems();

	void SetPromptText();
	bool PurchaseWeapon();

public:
	std::vector<Weapon> mWeapons;

	int mSelectedWeaponIndex = -1;

	EShoppingState mShoppingState = SS_MAIN;

	// Money Panel
	UIPanel mMoneyPanel;
	UIText mMoneyText;

	// Main Panel
	UIPanel mMainPanel;
	UIButton mMainBuyButton;
	UIButton mMainSellButton;
	UIButton mMainExitButton;

	// Buy Panel
	UIPanel mBuyMainPanel;
	UIButton mBuyMainWeaponsButton;
	UIButton mBuyMainArmourButton;
	UIButton mBuyMainItemsButton;

	// Weapons Panel
	UIPanel mWeaponSelectionPanel;
	UIButton mWeaponSelectionButtonOne;
	UIButton mWeaponSelectionButtonTwo;
	UIButton mWeaponSelectionButtonThree;
	UIButton mWeaponSelectionButtonFour;

	UIText mWeaponPriceTextOne;
	UIText mWeaponPriceTextTwo;
	UIText mWeaponPriceTextThree;
	UIText mWeaponPriceTextFour;

	// Purchase Prompt Panel
	UIPanel mPurchasePromptPanel;
	UIText mPurchasePromptText;

	// Weapon Purchase Confirm Panel
	UIPanel mWeaponConfirmPanel;
	UIButton mWeaponConfirmButtonYes;
	UIButton mWeaponConfirmButtonNo;
};