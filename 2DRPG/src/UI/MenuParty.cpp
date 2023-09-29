#include "MenuParty.h"

MenuParty::MenuParty()
{
    mIsMainMenu = true;

    mPartyButton.OnSelected = [this]()
    {
        mMainButtonIndex = 0;
    };
    mPartyButton.OnUpAction = [this]()
    {
        mCurrentButton = &mExitButton;
        mCurrentButton->OnSelected();
    };
    mPartyButton.OnDownAction = [this]()
    {
        mCurrentButton = &mStatusButton;
        mCurrentButton->OnSelected();
    };
    mPartyButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mStatusButton.OnSelected = [this]()
    {
        mMainButtonIndex = 1;
    };
    mStatusButton.OnUpAction = [this]()
    {
        mCurrentButton = &mPartyButton;
        mCurrentButton->OnSelected();
    };
    mStatusButton.OnDownAction = [this]()
    {
        mCurrentButton = &mInventoryButton;
        mCurrentButton->OnSelected();
    };
    mStatusButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mInventoryButton.OnSelected = [this]()
    {
        mMainButtonIndex = 2;
    };
    mInventoryButton.OnUpAction = [this]()
    {
        mCurrentButton = &mStatusButton;
        mCurrentButton->OnSelected();
    };
    mInventoryButton.OnDownAction = [this]()
    {
        mCurrentButton = &mJournalButton;
        mCurrentButton->OnSelected();
    };
    mInventoryButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mJournalButton.OnSelected = [this]()
    {
        mMainButtonIndex = 3;
    };
    mJournalButton.OnUpAction = [this]()
    {
        mCurrentButton = &mInventoryButton;
        mCurrentButton->OnSelected();
    };
    mJournalButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipButton;
        mCurrentButton->OnSelected();
    };
    mJournalButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mEquipButton.OnSelected = [this]()
    {
        mMainButtonIndex = 4;
    };
    mEquipButton.OnUpAction = [this]()
    {
        mCurrentButton = &mJournalButton;
        mCurrentButton->OnSelected();
    };
    mEquipButton.OnDownAction = [this]()
    {
        mCurrentButton = &mMagicButton;
        mCurrentButton->OnSelected();
    };
    mEquipButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mMagicButton.OnSelected = [this]()
    {
        mMainButtonIndex = 5;
    };
    mMagicButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipButton;
        mCurrentButton->OnSelected();
    };
    mMagicButton.OnDownAction = [this]()
    {
        mCurrentButton = &mExitButton;
        mCurrentButton->OnSelected();
    };
    mMagicButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mExitButton.OnSelected = [this]()
    {
        mMainButtonIndex = 6;
    };
    mExitButton.OnUpAction = [this]()
    {
        mCurrentButton = &mMagicButton;
        mCurrentButton->OnSelected();
    };
    mExitButton.OnDownAction = [this]()
    {
        mCurrentButton = &mPartyButton;
        mCurrentButton->OnSelected();
    };
    mExitButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mCurrentButton = &mPartyButton;
}

void MenuParty::Render(SDL_Renderer* renderer)
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
            optionsRect.y + TEXT_PADDING + TEXT_PADDING * i + Font::fontHeight * TEXT_SIZE * i,
            mMainMenuButtons[i]->mText.c_str());
    }

    GraphicsManager::DrawUISelector(
        optionsRect.x,
        optionsRect.y + TEXT_PADDING - TEXT_PADDING / 2 + Font::fontHeight * TEXT_SIZE * mMainButtonIndex + TEXT_PADDING * mMainButtonIndex,
        optionsRect.w,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    firstRect = GraphicsManager::DrawUIBox(
        firstRect.x + firstRect.w + UI_BOX_BORDER_SIZE * 3,
        firstRect.y,
        Font::fontWidth * TEXT_SIZE * 36 + Font::fontSpacing * TEXT_SIZE * 38 + TEXT_PADDING * 2,
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
            "Lv." + std::to_string(attributes.level) + ' ' + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel) + " Exp";

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE + TEXT_PADDING + characterYOffset,
            string.c_str());

        string =
            std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP " +
            std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2 + characterYOffset,
            string.c_str());
    }
}