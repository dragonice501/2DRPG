#pragma once

#include "Menu.h"

class MenuInteract : public Menu
{
public:
	MenuInteract();

	void Render(static SDL_Renderer* renderer) override;

	void DrawKeywordsPanel(static SDL_Renderer* renderer, SDL_Rect& rect);

	bool mIsInteractMenu = false;

	UIPanel mMainPanel;
	UIButton mTalkButton = UIButton("Talk");
	UIButton mAskButton = UIButton("Ask");
	UIButton mLeaveButton = UIButton("Leave");
	int mMainButtonIndex = 0;

	UIButton mPeopleButton = UIButton("People");
	UIButton mPlaces = UIButton("Places");
	UIButton mMysteries = UIButton("Mysteries");
	UIButton mBestiary = UIButton("Bestiary");

private:

	std::vector<UIButton*> mMainButtons =
	{
		&mTalkButton,
		&mAskButton,
		&mLeaveButton
	};
};