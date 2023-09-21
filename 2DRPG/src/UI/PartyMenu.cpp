#include "PartyMenu.h"

PartyMenu::PartyMenu()
{
    mPartyButton.OnUpAction = [this]()
    {
        mCurrentButton = &mExitButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mPartyButton.OnDownAction = [this]()
    {
        mCurrentButton = &mStatusButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };

    mStatusButton.OnUpAction = [this]()
    {
        mCurrentButton = &mPartyButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mStatusButton.OnDownAction = [this]()
    {
        mCurrentButton = &mInventoryButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };

    mInventoryButton.OnUpAction = [this]()
    {
        mCurrentButton = &mStatusButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mInventoryButton.OnDownAction = [this]()
    {
        mCurrentButton = &mJournalButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };

    mJournalButton.OnUpAction = [this]()
    {
        mCurrentButton = &mInventoryButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mJournalButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };

    mEquipButton.OnUpAction = [this]()
    {
        mCurrentButton = &mJournalButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mEquipButton.OnDownAction = [this]()
    {
        mCurrentButton = &mMagicButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };

    mMagicButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mMagicButton.OnDownAction = [this]()
    {
        mCurrentButton = &mExitButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };

    mExitButton.OnUpAction = [this]()
    {
        mCurrentButton = &mMagicButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mExitButton.OnDownAction = [this]()
    {
        mCurrentButton = &mPartyButton;
        std::cout << mCurrentButton->mText << " button selected" << std::endl;
    };
    mExitButton.OnAcceptAction = [this]()
    {
        
    };
}

void PartyMenu::Render(SDL_Renderer* renderer)
{
    SDL_Rect firstRect;
    std::string string;

    string = std::to_string(PlayerManager::GetPartyMoney()) + 'g';

    int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;

    firstRect = GraphicsManager::DrawUIBox(
        GraphicsManager::WindowWidth() / 2 - GraphicsManager::WindowWidth() / 4,
        GraphicsManager::WindowHeight() / 2 - GraphicsManager::WindowHeight() / 4,
        stringLength + TEXT_PADDING * 2,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2);

    GraphicsManager::DrawString(firstRect.x + TEXT_PADDING, firstRect.y + TEXT_PADDING, string.c_str());

    SDL_Rect optionsRect;
    optionsRect = GraphicsManager::DrawUIBox(
        firstRect.x,
        firstRect.y + Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2 + UI_BOX_BORDER_SIZE * 3,
        stringLength + TEXT_PADDING * 2,
        TEXT_PADDING * 2 + Font::fontHeight * TEXT_SIZE * 7 + TEXT_PADDING * (7 - 1));

    for (int i = 0; i < mMainMenuButtons.size(); i++)
    {
        GraphicsManager::DrawString(
            optionsRect.x + TEXT_PADDING,
            optionsRect.y + TEXT_PADDING + TEXT_PADDING * i + Font::fontHeight * TEXT_SIZE * i, mMainMenuButtons[i]->mText.c_str());
    }

    firstRect = GraphicsManager::DrawUIBox(
        firstRect.x + firstRect.w + UI_BOX_BORDER_SIZE * 3,
        firstRect.y,
        Font::fontWidth * TEXT_SIZE * 36 + Font::fontSpacing * TEXT_SIZE * 36 + TEXT_PADDING * 2,
        firstRect.h + optionsRect.h + UI_BOX_BORDER_SIZE * 3);

    for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
    {
        int characterXOffset = (Font::fontWidth * TEXT_SIZE * 20 + Font::fontSpacing * TEXT_SIZE * 20) * mCharacterUIPositions[i].x;
        int characterYOffset = (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 3 * mCharacterUIPositions[i].y;

        const CharacterAttributes& attributes = PlayerManager::GetCharacterAttributes()[i];

        string = attributes.characterName + "  " + GetClassName(attributes.characterClass);

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + characterYOffset,
            string.c_str());

        string =
            "Lv." + std::to_string(attributes.level) + ' ' + "Next Lv." + std::to_string(129);

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE + TEXT_PADDING + characterYOffset,
            string.c_str());

        string =
            std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP " +
            std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2 + characterYOffset,
            string.c_str());
    }
}