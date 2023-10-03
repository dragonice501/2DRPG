#include "MenuParty.h"

MenuParty::MenuParty() :
    mPartyButton("Party"), mStatusButton("Status"), mInventoryButton("Inventory"), mJournalButton("Journal"), mEquipButton("Equip"), mMagicButton("Magic"), mExitButton("Exit")
{
    mIsMainMenu = true;

    // Party Money
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

    // Main Options
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
    mPartyButton.OnAcceptAction = [this]()
    {
        mCurrentButton = &mFirstCharacterButton;
    };

    mStatusButton.OnSelected = [this]()
    {
        
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

    // Party Panel
    mPartyPanel.mIsActive = true;
    mPartyPanel.mPosition =
    {
        mMoneyPanel.mPosition.x + mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3,
        mMoneyPanel.mPosition.y
    };
    mPartyPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        mMoneyPanel.mSize.y + mMainPanel.mSize.y + UI_BOX_BORDER_SIZE * 3.0f
    };

    CharacterAttributes& attributes = PlayerManager::GetCharacterAttributes()[0];
    
    mFirstCharacterButton.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING,
        mPartyPanel.mPosition.y + TEXT_PADDING
    };
    mFirstCharacterButton.mText = attributes.characterName;

    std::string string;
    string = "Lv." + std::to_string(attributes.level);
    UIText text =
    {
        string,
        mFirstCharacterButton.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f)
    };
    mPartyPanel.mText.push_back(text);

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    text =
    {
        string,
        mFirstCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    text =
    {
        string,
        mFirstCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    text =
    {
        string,
        mFirstCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 3 + TEXT_PADDING * 3)
    };
    mPartyPanel.mText.push_back(text);

    mSecondCharacterButton.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING + mPartyPanel.mSize.x * 0.5f,
        mPartyPanel.mPosition.y + TEXT_PADDING
    };
    mSecondCharacterButton.mText = PlayerManager::GetCharacterAttributes()[1].characterName;

    attributes = PlayerManager::GetCharacterAttributes()[1];

    string = "Lv." + std::to_string(attributes.level);
    text =
    {
        string,
        mSecondCharacterButton.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f)
    };
    mPartyPanel.mText.push_back(text);

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    text =
    {
        string,
        mSecondCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    text =
    {
        string,
        mSecondCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    text =
    {
        string,
        mSecondCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 3 + TEXT_PADDING * 3)
    };
    mPartyPanel.mText.push_back(text);

    mThirdCharacterButton.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING,
        mPartyPanel.mPosition.y + TEXT_PADDING + mPartyPanel.mSize.y * 0.5f
    };
    mThirdCharacterButton.mText = PlayerManager::GetCharacterAttributes()[2].characterName;

    attributes = PlayerManager::GetCharacterAttributes()[2];

    string = "Lv." + std::to_string(attributes.level);
    text =
    {
        string,
        mThirdCharacterButton.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f)
    };
    mPartyPanel.mText.push_back(text);

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    text =
    {
        string,
        mThirdCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    text =
    {
        string,
        mThirdCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    text =
    {
        string,
        mThirdCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 3 + TEXT_PADDING * 3)
    };
    mPartyPanel.mText.push_back(text);

    mFourthCharacterButton.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING + mPartyPanel.mSize.x * 0.5f,
        mPartyPanel.mPosition.y + TEXT_PADDING + mPartyPanel.mSize.y * 0.5f
    };
    mFourthCharacterButton.mText = PlayerManager::GetCharacterAttributes()[3].characterName;

    attributes = PlayerManager::GetCharacterAttributes()[3];

    string = "Lv." + std::to_string(attributes.level);
    text =
    {
        string,
        mFourthCharacterButton.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f)
    };
    mPartyPanel.mText.push_back(text);

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    text =
    {
        string,
        mFourthCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    text =
    {
        string,
        mFourthCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2)
    };
    mPartyPanel.mText.push_back(text);

    string =
        std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    text =
    {
        string,
        mFourthCharacterButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE * 3 + TEXT_PADDING * 3)
    };
    mPartyPanel.mText.push_back(text);

    mFirstCharacterButton.OnDownAction = [this]()
    {
        mCurrentButton = &mThirdCharacterButton;
    };
    mFirstCharacterButton.OnRightAction = [this]()
    {
        mCurrentButton = &mSecondCharacterButton;
    };
    mFirstCharacterButton.OnAcceptAction = [this]()
    {

    };
    mFirstCharacterButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mSecondCharacterButton.OnDownAction = [this]()
    {
        mCurrentButton = &mFourthCharacterButton;
    };
    mSecondCharacterButton.OnLeftAction = [this]()
    {
        mCurrentButton = &mFirstCharacterButton;
    };
    mSecondCharacterButton.OnAcceptAction = [this]()
    {

    };
    mSecondCharacterButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mThirdCharacterButton.OnUpAction = [this]()
    {
        mCurrentButton = &mFirstCharacterButton;
    };
    mThirdCharacterButton.OnRightAction = [this]()
    {
        mCurrentButton = &mFourthCharacterButton;
    };
    mThirdCharacterButton.OnAcceptAction = [this]()
    {

    };
    mThirdCharacterButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mFourthCharacterButton.OnUpAction = [this]()
    {
        mCurrentButton = &mSecondCharacterButton;
    };
    mFourthCharacterButton.OnLeftAction = [this]()
    {
        mCurrentButton = &mThirdCharacterButton;
    };
    mFourthCharacterButton.OnAcceptAction = [this]()
    {

    };
    mFourthCharacterButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mPartyPanel.mButtons.push_back(&mFirstCharacterButton);
    mPartyPanel.mButtons.push_back(&mSecondCharacterButton);
    mPartyPanel.mButtons.push_back(&mThirdCharacterButton);
    mPartyPanel.mButtons.push_back(&mFourthCharacterButton);
    
    mCurrentButton = &mPartyButton;
}

void MenuParty::Render(SDL_Renderer* renderer)
{
    SDL_Rect firstRect;
    std::string string;

    if (mMoneyPanel.mIsActive) mMoneyPanel.Render();

    if (mMainPanel.mIsActive) mMainPanel.Render();

    if (mPartyPanel.mIsActive) mPartyPanel.Render();
}