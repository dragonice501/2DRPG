#include "MenuInteract.h"

MenuInteract::MenuInteract() :
    mTalkButton("Talk"), mAskButton("Ask"), mLeaveButton("Leave"),
    mPeopleButton("People"), mPlacesButton("Places"), mMysteriesButton("Mysteries"), mBestiaryButton("Bestiary"),
    mFirstButton("", Vec2(0.0f), false), mSecondButton("", Vec2(0.0f), false), mThirdButton("", Vec2(0.0f), false), mFourthButton("", Vec2(0.0f), false)
{
	mIsInteractMenu = true;

    SetupMainPanel();
    SetupAskPanel();
}

void MenuInteract::Render()
{
    if (mMainPanel.mIsActive)
    {
        mMainPanel.Render();
    }

    if (mAskingPanel.mIsActive)
    {
        mAskingPanel.Render();
    }

    if (mKeywordsPanel.mIsActive)
    {
        mKeywordsPanel.Render();
    }
}

void MenuInteract::SetupMainPanel()
{
    // Main Panel
    mMainPanel.mIsActive = true;
    mMainPanel.mPosition = { GraphicsManager::WindowWidth() / 2 - 150.0f, GraphicsManager::WindowHeight() / 2 - 50.0f };
    mMainPanel.mSize = { INTERACT_MENU_WIDTH, INTERACT_MENU_HEIGHT };
    mMainPanel.mButtons.push_back(&mTalkButton);
    mMainPanel.mButtons.push_back(&mAskButton);
    mMainPanel.mButtons.push_back(&mLeaveButton);

    mTalkButton.mPosition = mMainPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mAskButton.mPosition = mTalkButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_VERTICAL_PADDING * TEXT_SIZE);
    mLeaveButton.mPosition = mAskButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_VERTICAL_PADDING * TEXT_SIZE);
}

void MenuInteract::SetupAskPanel()
{
    // Asking Panel
    mAskingPanel.mIsActive = false;
    mAskingPanel.mPosition =
    {
        mMainPanel.mPosition.x + mMainPanel.mSize.x + UI_BOX_BORDER_SIZE * 3,
        mMainPanel.mPosition.y
    };

    std::string string = mPeopleButton.mText + mPlacesButton.mText + mMysteriesButton.mText + mBestiaryButton.mText;
    float size = Font::GetStringFontLength(string.c_str());
    mAskingPanel.mSize = { size * TEXT_SIZE + Font::fontWidth * 6 * TEXT_SIZE + TEXT_PADDING, Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f };

    mAskingPanel.mButtons.push_back(&mPeopleButton);
    mAskingPanel.mButtons.push_back(&mPlacesButton);
    mAskingPanel.mButtons.push_back(&mMysteriesButton);
    mAskingPanel.mButtons.push_back(&mBestiaryButton);

    mPeopleButton.mPosition = mAskingPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mPlacesButton.mPosition = mPeopleButton.mPosition + Vec2(Font::GetStringFontLength(mPeopleButton.mText.c_str()) * TEXT_SIZE + Font::fontWidth * TEXT_SIZE * 2, 0.0f);
    mMysteriesButton.mPosition = mPlacesButton.mPosition + Vec2(Font::GetStringFontLength(mPlacesButton.mText.c_str()) * TEXT_SIZE + Font::fontWidth * TEXT_SIZE * 2, 0.0f);
    mBestiaryButton.mPosition = mMysteriesButton.mPosition + Vec2(Font::GetStringFontLength(mMysteriesButton.mText.c_str()) * TEXT_SIZE + Font::fontWidth * TEXT_SIZE * 2, 0.0f);

    // Keywords Pannel
    mKeywordsPanel.mIsActive = false;
    mKeywordsPanel.mPosition =
    {
        mAskingPanel.mPosition.x,
        mAskingPanel.mPosition.y + mAskingPanel.mSize.y + UI_BOX_BORDER_SIZE * 3
    };
    mKeywordsPanel.mSize = { mAskingPanel.mSize.x, TEXT_PADDING * TEXT_SIZE * 2.0f + Font::fontHeight * TEXT_SIZE * 3.0f };

    mKeywordsPanel.mButtons.push_back(&mFirstButton);
    mKeywordsPanel.mButtons.push_back(&mSecondButton);
    mKeywordsPanel.mButtons.push_back(&mThirdButton);
    mKeywordsPanel.mButtons.push_back(&mFourthButton);
    mKeywordsPanel.mButtons.push_back(&mFifthButton);
    mKeywordsPanel.mButtons.push_back(&mSixthButton);

    mFirstButton.mPosition = mKeywordsPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mThirdButton.mPosition = mFirstButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mFifthButton.mPosition = mThirdButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    mSecondButton.mPosition = mFirstButton.mPosition + Vec2(mKeywordsPanel.mSize.x / 2.0f, 0.0f);
    mFourthButton.mPosition = mSecondButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mSixthButton.mPosition = mFourthButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
}

void MenuInteract::DrawKeywordsPanel(SDL_Renderer* renderer, SDL_Rect& rect)
{
    rect = GraphicsManager::DrawUIBox(
        rect.x + rect.w + UI_BOX_BORDER_SIZE * 3,
        rect.y,
        300,
        rect.h);

    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, "People");
    GraphicsManager::DrawString(rect.x + TEXT_PADDING + 100, rect.y + TEXT_PADDING, "Places");
    GraphicsManager::DrawString(rect.x + TEXT_PADDING + 200, rect.y + TEXT_PADDING, "Mysteries");
    GraphicsManager::DrawString(rect.x + TEXT_PADDING + 300, rect.y + TEXT_PADDING, "Bestiary");
}

void MenuInteract::FillKeywordPanel(const EKeywordMenu type)
{
    mFirstButton.mIsActive = false;
    mSecondButton.mIsActive = false;
    mThirdButton.mIsActive = false;
    mFourthButton.mIsActive = false;
    mFifthButton.mIsActive = false;
    mSixthButton.mIsActive = false;

    const std::vector<std::string>* stringVec = nullptr;
    switch (type)
    {
        case PEOPLE:
        {
            stringVec = &PlayerManager::GetPeopleKeywords();
            break;
        }
        case PLACES:
        {
            stringVec = &PlayerManager::GetPlacesKeywords();
            break;
        }
        case MYSTERIES:
        {
            stringVec = &PlayerManager::GetMysteryKeywords();
            break;
        }
        case BESTIARY:
        {
            stringVec = &PlayerManager::GetBestiaryKeywords();
            break;
        }
    }

    if (stringVec->size() > 0)
    {
        for (int i = 0; i < mKeywordsPanel.mButtons.size(); i++)
        {
            if (i > stringVec->size() - 1) break;

            mKeywordsPanel.mButtons[i]->mIsActive = true;
            mKeywordsPanel.mButtons[i]->mText = stringVec->at(i);
        }
    }
}