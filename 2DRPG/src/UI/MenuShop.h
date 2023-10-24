#pragma once

#include "Menu.h"

#include "../Items/Weapon.h"
#include "../Items/Armour.h"

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
	void SetupArmourSelectionPanel();

	void SetupWeaponPurchasePromptPanel();
	void SetupArmourPurchasePromptPanel();

	void FillBuyButtonsWeapons();
	void FillBuyButtonsArmour();
	void FillBuyButtonsItems();

	void SetWeaponPromptText();
	void SetArmourPromptText();

	bool PurchaseWeapon();
	bool PurchaseArmour();

public:
	std::vector<Weapon> mWeapons;
	std::vector<Armour> mArmour;

	int mSelectedWeaponIndex = -1;
	int mSelectedArmourIndex = -1;

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

	// Armour Panel
	UIPanel mArmourSelectionPanel;
	UIButton mArmourSelectionButtonOne;
	UIButton mArmourSelectionButtonTwo;
	UIButton mArmourSelectionButtonThree;
	UIButton mArmourSelectionButtonFour;

	UIText mArmourPriceTextOne;
	UIText mArmourPriceTextTwo;
	UIText mArmourPriceTextThree;
	UIText mArmourPriceTextFour;

	// Waepon Purchase Prompt Panel
	UIPanel mWeaponPurchasePromptPanel;
	UIText mWeaponPurchasePromptText;

	// Weapon Purchase Confirm Panel
	UIPanel mWeaponConfirmPanel;
	UIButton mWeaponConfirmButtonYes;
	UIButton mWeaponConfirmButtonNo;

	// Armour Purchase Prompt Panel
	UIPanel mArmourPurchasePromptPanel;
	UIText mArmourPurchasePromptText;

	// Armour Purchase Confirm Panel
	UIPanel mArmourConfirmPanel;
	UIButton mArmourConfirmButtonYes;
	UIButton mArmourConfirmButtonNo;
};