#pragma once

#include "UIButton.h"

#include "../Managers/GraphicsManager.h"

#include "../Utils/Vec2.h"

#include <vector>

class UIPanel
{
public:
	UIPanel() {}

	void SetButtons(const std::vector<UIButton*>& buttons) { mButtons = buttons; }

	void Render()
	{
		GraphicsManager::DrawUIBox(mPosition.x, mPosition.y, mSize.x, mSize.y);

		for (UIButton* button : mButtons)
		{
			if(button->mIsActive)
				button->Render();
		}
	}

	bool mIsActive = false;
	Vec2 mPosition;
	Vec2 mSize;

	std::vector<UIButton*> mButtons;
};