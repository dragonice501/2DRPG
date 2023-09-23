#pragma once

#include "Menu.h"

class MenuInteract : public Menu
{
public:
	MenuInteract();

	void Render(static SDL_Renderer* renderer) override;

	bool mIsInteractMenu = false;

	UIButton mTalkButton = UIButton("Talk");
	UIButton mAskButton = UIButton("Ask");
	UIButton mLeaveButton = UIButton("Leave");
	int mMainButtonIndex = 0;

private:
	std::vector<UIButton*> mMainButtons =
	{
		&mTalkButton,
		&mAskButton,
		&mLeaveButton
	};
};