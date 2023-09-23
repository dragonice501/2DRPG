#include "MenuInteract.h"

MenuInteract::MenuInteract()
{
	mIsInteractMenu = true;
}

void MenuInteract::Render(SDL_Renderer* renderer)
{
    SDL_Rect rect = GraphicsManager::DrawUIBox(GraphicsManager::WindowWidth() / 2 - 150, GraphicsManager::WindowHeight() / 2 - 50, INTERACT_MENU_WIDTH, INTERACT_MENU_HEIGHT);

    for (int i = 0; i < mMainButtons.size(); i++)
    {
        GraphicsManager::DrawString(
            rect.x + TEXT_PADDING,
            rect.y + TEXT_PADDING + TEXT_PADDING * i + Font::fontHeight * TEXT_SIZE * i,
            mMainButtons[i]->mText.c_str());
    }

    GraphicsManager::DrawUISelector(
        rect.x,
        rect.y + TEXT_PADDING - TEXT_PADDING / 2 + Font::fontHeight * TEXT_SIZE * mMainButtonIndex + TEXT_PADDING * mMainButtonIndex,
        rect.w,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
}
