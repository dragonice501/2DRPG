#pragma once

#include "SceneExploration.h"

#include "Weapon.h"

#include "MenuShop.h"

class SceneTownShop : public SceneExploration
{
public:
	SceneTownShop() : SceneTownShop("TownShop")
	{
		SetupShopMenu();
	}
	SceneTownShop(std::string fileName)
	{
		mFileName = fileName;
	}
	~SceneTownShop();

	void Setup(static SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(const float dt) override;
	void Render(static SDL_Rect& camera) override;

	void DrawCursor() override;

	void SetupShopMenu();

	void LoadShopItems();

	MenuShop mShopMenu;
};