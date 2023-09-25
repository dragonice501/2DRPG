#pragma once

#include "UIButton.h"
#include "UIPanel.h"

#include "../Managers/GameManager.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/PlayerManager.h"
#include "../Graphics/Font.h"

#include "../Utils/Vec2.h"

#include <SDL.h>
#include <vector>

class Menu
{
public:
	virtual ~Menu() {}

	inline UIButton* GetCurrentButton() const { return mCurrentButton; }
	inline UIButton* GetPreviousButton() const { return mPreviousButton; }

	inline void SetCurrentButton(UIButton* button) { mCurrentButton = button; }
	inline void SetPreviousButton(UIButton* button) { mPreviousButton = button; }

	inline void CurrentButtonSelect()
	{
		if (mCurrentButton->OnSelected)
		{
			mCurrentButton->OnSelected();
		}
	}
	inline void PreviousButtonSelect()
	{
		if (mPreviousButton->OnSelected)
		{
			mPreviousButton->OnSelected();
		}
	}

	virtual void Render(static SDL_Renderer* renderer) = 0;

protected:
	UIButton* mCurrentButton;
	UIButton* mPreviousButton;
};