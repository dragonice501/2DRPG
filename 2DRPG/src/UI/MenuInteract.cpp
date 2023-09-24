#include "MenuInteract.h"

MenuInteract::MenuInteract()
{
	mIsInteractMenu = true;

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

void MenuInteract::Render(SDL_Renderer* renderer)
{
    if (mMainPanel.mIsActive)
    {
        mMainPanel.Render();
        mTalkButton.Render();
        mAskButton.Render();
        mLeaveButton.Render();

        GraphicsManager::DrawUISelector(
            mMainPanel.mPosition.mPosition.x,
            mMainPanel.mPosition.y + TEXT_PADDING - TEXT_PADDING / 2 + Font::fontHeight * TEXT_SIZE * mMainButtonIndex + TEXT_PADDING * mMainButtonIndex,
            mMainPanel.mSize.x,
            Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    }
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
