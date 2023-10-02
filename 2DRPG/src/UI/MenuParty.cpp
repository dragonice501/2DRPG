#include "MenuParty.h"

MenuParty::MenuParty() :
    mPartyButton("Party"), mStatusButton("Status"), mInventoryButton("Inventory"), mJournalButton("Journal"), mEquipButton("Equip"), mMagicButton("Magic"), mExitButton("Exit")
{
    mIsMainMenu = true;

    mMoneyPanel.mIsActive = true;
    int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;
    mMoneyPanel.mPosition =
    {
        GraphicsManager::WindowWidth() / 2.0f - GraphicsManager::WindowWidth() / 4.0f,
        GraphicsManager::WindowHeight() / 2.0f - GraphicsManager::WindowHeight() / 4.0f
    };
    mMoneyPanel.mSize =
    {
        stringLength + TEXT_PADDING * 2.0f,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
    };

    UIText moneyText = { "10000g" };
    moneyText.mPosition = { mMoneyPanel.mPosition.x + TEXT_PADDING, mMoneyPanel.mPosition.y + TEXT_PADDING };
    mMoneyPanel.mText.push_back(moneyText);

    mMainPanel.mIsActive = true;
    mMainPanel.mPosition =
    {
        mMoneyPanel.mPosition.x,
        mMoneyPanel.mPosition.y + Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2 + UI_BOX_BORDER_SIZE * 3
    };
    mMainPanel.mSize =
    {
        stringLength + TEXT_PADDING * 2.0f,
        TEXT_PADDING * 2.0f + Font::fontHeight * TEXT_SIZE * 7.0f + TEXT_PADDING * 6.0f
    };

    mMainPanel.mButtons.push_back(&mPartyButton);
    mMainPanel.mButtons.push_back(&mStatusButton);
    mMainPanel.mButtons.push_back(&mInventoryButton);
    mMainPanel.mButtons.push_back(&mJournalButton);
    mMainPanel.mButtons.push_back(&mEquipButton);
    mMainPanel.mButtons.push_back(&mMagicButton);
    mMainPanel.mButtons.push_back(&mExitButton);

    float vertOffset = Font::fontHeight * TEXT_SIZE + TEXT_PADDING;
    mPartyButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING };
    mStatusButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING + vertOffset };
    mInventoryButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING + vertOffset * 2 };
    mJournalButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING + vertOffset * 3 };
    mEquipButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING + vertOffset * 4 };
    mMagicButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING + vertOffset * 5 };
    mExitButton.mPosition = { mMainPanel.mPosition.x + TEXT_PADDING, mMainPanel.mPosition.y + TEXT_PADDING + vertOffset * 6 };

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

    if (mMoneyPanel.mIsActive) mMoneyPanel.Render();

    if (mMainPanel.mIsActive) mMainPanel.Render();
}