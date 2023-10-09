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
	inline UIButton* GetPreviousButton() const { return mPreviousButtonFirst; }

	inline void SetCurrentButton(UIButton* button) { mCurrentButton = button; }
	inline void SetPreviousButton(UIButton* button) { mPreviousButtonFirst = button; }

	inline void SelectPreviousButtonFirst()
	{
		if (mPreviousButtonFirst) mCurrentButton = mPreviousButtonFirst;
	}
	inline void SelectPreviousButtonSecond()
	{
		if (mPreviousButtonSecond) mCurrentButton = mPreviousButtonSecond;
	}
	inline void SelectPreviousButtonThird()
	{
		if (mPreviousButtonThird) mCurrentButton = mPreviousButtonThird;
	}

	inline void CurrentButtonSelect()
	{
		if (mCurrentButton->OnSelected)
		{
			mCurrentButton->OnSelected();
		}
	}
	inline void PreviousButtonSelect()
	{
		if (mPreviousButtonFirst->OnSelected)
		{
			mPreviousButtonFirst->OnSelected();
		}
	}

	virtual void Render(static SDL_Renderer* renderer) = 0;

protected:
	UIButton* mCurrentButton;
	UIButton* mPreviousButtonFirst;
	UIButton* mPreviousButtonSecond;
	UIButton* mPreviousButtonThird;
};