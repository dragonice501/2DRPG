#pragma once

#include "../Managers/GraphicsManager.h"

#include "../Utils/Vec2.h"

#include<string>

class UIText
{
public:
	UIText(const std::string& text = "", const Vec2& position = Vec2(0.0f))
	{
		this->mText = text;
		this->mPosition = position;
	}

	void Render()
	{
		GraphicsManager::DrawString(mPosition.x, mPosition.y, mText.c_str());
	}

	std::string mText;
	Vec2 mPosition;
};