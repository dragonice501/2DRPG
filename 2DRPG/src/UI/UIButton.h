#pragma once

#include "../Utils/Vec2.h"

#include <iostream>
#include <string>
#include <functional>
#include <SDL.h>

class UIButton
{
public:
	UIButton(const std::string& text = "")
	{
		this->mText = text;
	}

	void Render(static SDL_Renderer* renderer);

	std::string mText;
	Vec2 mPosition;

	using ButtonAction = std::function<void()>;

	ButtonAction OnSelected;
	ButtonAction OnUpAction;
	ButtonAction OnDownAction;
	ButtonAction OnRightAction;
	ButtonAction OnLeftAction;
	ButtonAction OnAcceptAction;
	ButtonAction OnCancelAction;
};