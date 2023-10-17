#pragma once

#include "Menu.h"

class MenuInteract : public Menu
{
public:
	enum EKeywordMenu
	{
		PEOPLE,
		PLACES,
		MYSTERIES,
		BESTIARY
	};

public:
	MenuInteract();

	inline const EKeywordMenu GetKeywordType() const { return mKeywordType; }
	inline void SetKeywordType(const EKeywordMenu type) { mKeywordType = type; }

	void Render() override;

	void SetupMainPanel();
	void SetupAskPanel();

	void DrawKeywordsPanel(static SDL_Renderer* renderer, SDL_Rect& rect);

	bool mIsInteractMenu = false;

	UIPanel mMainPanel;
	UIButton mTalkButton;
	UIButton mAskButton;
	UIButton mLeaveButton;
	int mMainButtonIndex = 0;

	UIPanel mAskingPanel;
	UIButton mPeopleButton;
	UIButton mPlacesButton;
	UIButton mMysteriesButton;
	UIButton mBestiaryButton;

	UIPanel mKeywordsPanel;
	UIButton mFirstButton;
	UIButton mSecondButton;
	UIButton mThirdButton;
	UIButton mFourthButton;
	UIButton mFifthButton;
	UIButton mSixthButton;

	void FillKeywordPanel(const EKeywordMenu type);

private:
	EKeywordMenu mKeywordType;

	std::vector<UIButton*> mMainButtons =
	{
		&mTalkButton,
		&mAskButton,
		&mLeaveButton
	};
};