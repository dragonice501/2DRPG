#pragma once

#include "Menu.h"

class MenuShop : public Menu
{
public:
	MenuShop();

	void Render() override;

	void SetupMainPanel();

public:
	UIPanel mMainPanel;
	UIButton mMainBuyButton;
	UIButton mMainSellButton;
	UIButton mMainExitButton;
};