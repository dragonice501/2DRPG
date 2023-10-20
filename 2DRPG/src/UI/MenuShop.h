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

	UIPanel mMoneyPanel;
	UIText mMoneyText;

	UIPanel mMainPanel;
	UIButton mMainBuyButton;
	UIButton mMainSellButton;
	UIButton mMainExitButton;

	UIPanel mBuyMainPanel;
	UIButton mBuyMainWeaponsButton;
	UIButton mBuyMainArmourButton;
	UIButton mBuyMainItemsButton;

	UIPanel mWeaponSelectionPanel;
	UIButton mWeaponSelectionButtonOne;
	UIButton mWeaponSelectionButtonTwo;
	UIButton mWeaponSelectionButtonThree;
	UIButton mWeaponSelectionButtonFour;

	UIText mWeaponPriceTextOne;
	UIText mWeaponPriceTextTwo;
	UIText mWeaponPriceTextThree;
	UIText mWeaponPriceTextFour;

	UIPanel mPurchasePromptPanel;
	UIText mPurchasePromptText;

	UIPanel mWeaponConfirmPanel;
	UIButton mWeaponConfirmButtonYes;
	UIButton mWeaponConfirmButtonNo;
};