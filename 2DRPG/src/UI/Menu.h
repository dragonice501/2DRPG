#pragma once

#include "UIButton.h"
#include "UIPanel.h"
#include "UISprite.h"

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

	virtual void Render() = 0;

	inline Vec2 CalcWindowPositionFromUV(const Vec2& positionUV) const
	{ 
		return Vec2(positionUV.x * GraphicsManager::WindowWidth(), positionUV.y * GraphicsManager::WindowHeight());
	}
	inline Vec2 CalcWindowUVFromPosition(const Vec2& UV) const
	{
		return Vec2(UV.x / GraphicsManager::WindowWidth(), UV.y / GraphicsManager::WindowHeight());
	}

protected:
	UIButton* mCurrentButton;
	UIButton* mPreviousButtonFirst;
	UIButton* mPreviousButtonSecond;
	UIButton* mPreviousButtonThird;
};