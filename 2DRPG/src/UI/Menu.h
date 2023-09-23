#pragma once

#include "UIButton.h"

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

	const UIButton& GetCurrentButton() const { return *mCurrentButton; }
	void SetCurrentButton(UIButton* button) { mCurrentButton = button; }

	virtual void Render(static SDL_Renderer* renderer) = 0;

protected:
	UIButton* mCurrentButton;
};