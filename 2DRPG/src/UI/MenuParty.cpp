#include "MenuParty.h"

MenuParty::MenuParty() :
    mPartyButton("Party"), mStatusButton("Status"), mInventoryButton("Inventory"), mJournalButton("Journal"), mEquipButton("Equip"), mMagicButton("Magic"), mExitButton("Exit"),
    mJournalButtonOne("People"), mJournalButtonTwo("Place"), mJournalButtonThree("Mystery"), mJournalButtonFour("Bestiary"),
    mInventoryButtonOne("Items"), mInventoryButtonTwo("Weapons"), mInventoryButtonThree("Armour"),
    mEquipOptionsButtonEquip("Equip"), mEquipOptionsButtonRemove("Remove"), mEquipOptionsButtonRemoveAll("Remove All"), mEquipOptionsButtonOptimize("Optimize")
{
    mIsMainMenu = true;

    SetupMoneyPanel();
    SetupMainPanel();
    SetupPartyPanel();
    SetupStatusPanel();
    SetupInventoryPanel();
    SetupJournalPanel();
    SetupEquipPanel();

    mCurrentButton = &mPartyButton;
}

void MenuParty::Render()
{
    SDL_Rect firstRect;
    std::string string;

    if (mMoneyPanel.mIsActive) mMoneyPanel.Render();

    if (mMainPanel.mIsActive) mMainPanel.Render();

    switch (mPanelState)
    {
        case MenuParty::PS_PARTY:
        {
            mPartyPanel.Render();
            break;
        }
        case MenuParty::PS_STATUS:
        {
            mStatusButtonPanel.Render();
            mStatusAttributesPanel.Render();

            mStatusLevelText.Render();
            mStatusClassText.Render();
            mStatusHPText.Render();
            mStatusMPText.Render();
            mStatusCurrentXPText.Render();
            mStatusNextLevelText.Render();
            mStatusStrengthText.Render();
            mStatusDefenseText.Render();
            mStatusIntelligenceText.Render();
            mStatusSpeedText.Render();
            mStatusSkillText.Render();
            mStatusLuckText.Render();
            break;
        }
        case MenuParty::PS_INVENTORY:
        {
            mInventoryButtonsPanel.Render();
            mInventoryPanel.Render();
            break;
        }
        case MenuParty::PS_JOURNAL:
        {
            mJournalButtonsPanel.Render();
            mJournalKeywordsPanel.Render();
            break;
        }
        case MenuParty::PS_EQUIP:
        {
            mEquipButtonsPanel.Render();
            mEquipmentPanel.Render();

            mEquipOptionsPanel.Render();

            mEquipmentWeaponText.Render();
            mEquipmentShieldText.Render();
            mEquipmentHeadText.Render();
            mEquipmentChestText.Render();
            mEquipmentArmsText.Render();
            mEquipmentLegsText.Render();
            break;
        }
        case MenuParty::PS_MAGIC:
        {
            break;
        }
        case MenuParty::PS_SELECTING_WEAPON:
        {
            mInventoryPanel.Render();
        }
    }
}

void MenuParty::SetupMoneyPanel()
{
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

    mMoneyText.mPosition =
    {
        mMoneyPanel.mPosition.x + TEXT_PADDING,
        mMoneyPanel.mPosition.y + TEXT_PADDING
    };
    mMoneyText.mReference = &PlayerManager::mPartyGold;
    mMoneyText.mText = 'g';
    mMoneyPanel.mText.push_back(&mMoneyText);
}

void MenuParty::SetupMainPanel()
{
    int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;
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
    mPartyButton.OnDownAction = [this]()
    {
        mCurrentButton = &mStatusButton;
        mCurrentButton->OnSelected();
    };
    mPartyButton.OnAcceptAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mPartyButtonOne;
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
    mStatusButton.OnAcceptAction = [this]()
    {
        SetStatusButtonsText();
        SetPanelState(PS_STATUS);
        SetStatusCharacterAttributes(0);
        mCurrentButton = &mStatusButtonOne;
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
    mInventoryButton.OnAcceptAction = [this]()
    {
        SetPanelState(PS_INVENTORY);
        FillInventoryItemButtons();
        mCurrentButton = &mInventoryButtonOne;
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
    mJournalButton.OnAcceptAction = [this]()
    {
        SetPanelState(PS_JOURNAL);
        mCurrentButton = &mJournalButtonOne;
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
    mEquipButton.OnAcceptAction = [this]()
    {
        SetEquipButtonsText();
        FillEquipmentText(0);
        SetPanelState(PS_EQUIP);
        mCurrentButton = &mEquipButtonOne;
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
    mExitButton.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };
}

void MenuParty::SetupPartyPanel()
{
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

    mPartyButtonOne.OnDownAction = [this]()
    {
        mCurrentButton = &mPartyButtonThree;
    };
    mPartyButtonOne.OnRightAction = [this]()
    {
        mCurrentButton = &mPartyButtonTwo;
    };
    mPartyButtonOne.OnAcceptAction = [this]()
    {

    };
    mPartyButtonOne.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mPartyButtonTwo.OnDownAction = [this]()
    {
        mCurrentButton = &mPartyButtonFour;
    };
    mPartyButtonTwo.OnLeftAction = [this]()
    {
        mCurrentButton = &mPartyButtonOne;
    };
    mPartyButtonTwo.OnAcceptAction = [this]()
    {

    };
    mPartyButtonTwo.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mPartyButtonThree.OnUpAction = [this]()
    {
        mCurrentButton = &mPartyButtonOne;
    };
    mPartyButtonThree.OnRightAction = [this]()
    {
        mCurrentButton = &mPartyButtonFour;
    };
    mPartyButtonThree.OnAcceptAction = [this]()
    {

    };
    mPartyButtonThree.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mPartyButtonFour.OnUpAction = [this]()
    {
        mCurrentButton = &mPartyButtonTwo;
    };
    mPartyButtonFour.OnLeftAction = [this]()
    {
        mCurrentButton = &mPartyButtonThree;
    };
    mPartyButtonFour.OnAcceptAction = [this]()
    {

    };
    mPartyButtonFour.OnCancelAction = [this]()
    {
        mCurrentButton = &mPartyButton;
    };

    mPartyPanel.mButtons.push_back(&mPartyButtonOne);
    mPartyPanel.mButtons.push_back(&mPartyButtonTwo);
    mPartyPanel.mButtons.push_back(&mPartyButtonThree);
    mPartyPanel.mButtons.push_back(&mPartyButtonFour);

    // First Character
    mPartyButtonOne.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING,
        mPartyPanel.mPosition.y + TEXT_PADDING
    };

    mPartyLevelTextOne.mPosition = mPartyButtonOne.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f);
    mPartyClassTextOne.mPosition = mPartyButtonOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyHPTextOne.mPosition = mPartyClassTextOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyMPTextOne.mPosition = mPartyHPTextOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    
    mPartyPanel.mText.push_back(&mPartyLevelTextOne);
    mPartyPanel.mText.push_back(&mPartyClassTextOne);
    mPartyPanel.mText.push_back(&mPartyHPTextOne);
    mPartyPanel.mText.push_back(&mPartyMPTextOne);

    // Second Character
    mPartyButtonTwo.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING + mPartyPanel.mSize.x * 0.5f,
        mPartyPanel.mPosition.y + TEXT_PADDING
    };

    mPartyLevelTextTwo.mPosition = mPartyButtonTwo.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f);
    mPartyClassTextTwo.mPosition = mPartyButtonTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyHPTextTwo.mPosition = mPartyClassTextTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyMPTextTwo.mPosition = mPartyHPTextTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    mPartyPanel.mText.push_back(&mPartyLevelTextTwo);
    mPartyPanel.mText.push_back(&mPartyClassTextTwo);
    mPartyPanel.mText.push_back(&mPartyHPTextTwo);
    mPartyPanel.mText.push_back(&mPartyMPTextTwo);

    // Third Character
    mPartyButtonThree.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING,
        mPartyPanel.mPosition.y + TEXT_PADDING + mPartyPanel.mSize.y * 0.5f
    };

    mPartyLevelTextThree.mPosition = mPartyButtonThree.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f);
    mPartyClassTextThree.mPosition = mPartyButtonThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyHPTextThree.mPosition = mPartyClassTextThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyMPTextThree.mPosition = mPartyHPTextThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    mPartyPanel.mText.push_back(&mPartyLevelTextThree);
    mPartyPanel.mText.push_back(&mPartyClassTextThree);
    mPartyPanel.mText.push_back(&mPartyHPTextThree);
    mPartyPanel.mText.push_back(&mPartyMPTextThree);

    // Four Character
    mPartyButtonFour.mPosition =
    {
        mPartyPanel.mPosition.x + TEXT_PADDING + mPartyPanel.mSize.x * 0.5f,
        mPartyPanel.mPosition.y + TEXT_PADDING + mPartyPanel.mSize.y * 0.5f
    };

    mPartyLevelTextFour.mPosition = mPartyButtonFour.mPosition + Vec2(mPartyPanel.mSize.x * 0.25f, 0.0f);
    mPartyClassTextFour.mPosition = mPartyButtonFour.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyHPTextFour.mPosition = mPartyClassTextFour.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mPartyMPTextFour.mPosition = mPartyHPTextFour.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    mPartyPanel.mText.push_back(&mPartyLevelTextFour);
    mPartyPanel.mText.push_back(&mPartyClassTextFour);
    mPartyPanel.mText.push_back(&mPartyHPTextFour);
    mPartyPanel.mText.push_back(&mPartyMPTextFour);

    FillPartyAttributes();
}

void MenuParty::SetupStatusPanel()
{
    mStatusButtonPanel.mIsActive = false;
    mStatusButtonPanel.mPosition =
    {
        mMoneyPanel.mPosition.x + mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3,
        mMoneyPanel.mPosition.y
    };
    mStatusButtonPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        Font::fontHeight* TEXT_SIZE + TEXT_PADDING * 2.0f
    };

    mStatusButtonOne.mPosition = mStatusButtonPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mStatusButtonTwo.mPosition = mStatusButtonPanel.mPosition + Vec2(mStatusButtonPanel.mSize.x * 0.25f, TEXT_PADDING);
    mStatusButtonThree.mPosition = mStatusButtonPanel.mPosition + Vec2(mStatusButtonPanel.mSize.x * 0.5f, TEXT_PADDING);
    mStatusButtonFour.mPosition = mStatusButtonPanel.mPosition + Vec2(mStatusButtonPanel.mSize.x * 0.75f, TEXT_PADDING);

    mStatusButtonOne.OnRightAction = [this]()
    {
        mCurrentButton = &mStatusButtonTwo;
        SetStatusCharacterAttributes(1);
    };
    mStatusButtonOne.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mStatusButton;
    };

    mStatusButtonTwo.OnLeftAction = [this]()
    {
        mCurrentButton = &mStatusButtonOne;
        SetStatusCharacterAttributes(0);
    };
    mStatusButtonTwo.OnRightAction = [this]()
    {
        mCurrentButton = &mStatusButtonThree;
        SetStatusCharacterAttributes(2);
    };
    mStatusButtonTwo.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mStatusButton;
    };

    mStatusButtonThree.OnLeftAction = [this]()
    {
        mCurrentButton = &mStatusButtonTwo;
        SetStatusCharacterAttributes(1);
    };
    mStatusButtonThree.OnRightAction = [this]()
    {
        mCurrentButton = &mStatusButtonFour;
        SetStatusCharacterAttributes(3);
    };
    mStatusButtonThree.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mStatusButton;
    };

    mStatusButtonFour.OnLeftAction = [this]()
    {
        mCurrentButton = &mStatusButtonThree;
        SetStatusCharacterAttributes(2);
    };
    mStatusButtonFour.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mStatusButton;
    };

    mStatusButtonPanel.mButtons.push_back(&mStatusButtonOne);
    mStatusButtonPanel.mButtons.push_back(&mStatusButtonTwo);
    mStatusButtonPanel.mButtons.push_back(&mStatusButtonThree);
    mStatusButtonPanel.mButtons.push_back(&mStatusButtonFour);

    mStatusAttributesPanel.mPosition =
    {
        mStatusButtonPanel.mPosition.x,
        mMainPanel.mPosition.y
    };
    mStatusAttributesPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        TEXT_PADDING * 2.0f + Font::fontHeight * TEXT_SIZE * 7.0f + TEXT_PADDING * 6.0f
    };

    float fontLength;

    // Level
    mStatusLevelText.mPosition = mStatusAttributesPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mStatusLevelText.mText = "Lv. ";
    mStatusAttributesPanel.mText.push_back(&mStatusLevelText);

    fontLength = Font::GetStringFontLength(mStatusLevelText.mText.c_str()) * TEXT_SIZE;
    mStatusLevelValueText.mPosition = mStatusLevelText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusLevelValueText);

    // Class
    mStatusClassText.mPosition = mStatusLevelText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusClassText.mText = GetClassName(PlayerManager::GetCharacterAttributes()[0].characterClass);

    fontLength = Font::GetStringFontLength(mStatusClassText.mText.c_str()) * TEXT_SIZE;
    mStatusClassValueText.mPosition = mStatusClassText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

     // HP
    mStatusHPText.mPosition = mStatusClassText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusHPText.mText = "HP ";
    mStatusAttributesPanel.mText.push_back(&mStatusHPText);

    fontLength = Font::GetStringFontLength(mStatusHPText.mText.c_str()) * TEXT_SIZE;
    mStatusHPValueText.mPosition = mStatusHPText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusHPValueText);

    // MP
    mStatusMPText.mPosition = mStatusHPText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusMPText.mText = "MP ";
    mStatusAttributesPanel.mText.push_back(&mStatusMPText);

    fontLength = Font::GetStringFontLength(mStatusMPText.mText.c_str()) * TEXT_SIZE;
    mStatusMPValueText.mPosition = mStatusMPText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusMPValueText);
     
    // EXP
    mStatusCurrentXPText.mPosition = mStatusMPText.mPosition + Vec2(0.0f, (Font::fontHeight * TEXT_SIZE) * 2 + TEXT_PADDING * 2);
    mStatusCurrentXPText.mText = "Current Exp ";
    mStatusAttributesPanel.mText.push_back(&mStatusCurrentXPText);

    fontLength = Font::GetStringFontLength(mStatusCurrentXPText.mText.c_str()) * TEXT_SIZE;
    mStatusCurrentXPValueText.mPosition = mStatusCurrentXPText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusCurrentXPValueText);

    // Next Level
    mStatusNextLevelText.mPosition = mStatusCurrentXPText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusNextLevelText.mText = "Next Level ";
    mStatusAttributesPanel.mText.push_back(&mStatusNextLevelText);

    fontLength = Font::GetStringFontLength(mStatusNextLevelText.mText.c_str()) * TEXT_SIZE;
    mStatusNextLevelValueText.mPosition = mStatusNextLevelText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusNextLevelValueText);

    // Strength
    mStatusStrengthText.mPosition = mStatusAttributesPanel.mPosition + Vec2(mStatusAttributesPanel.mSize.x * 0.5f, TEXT_PADDING);
    mStatusStrengthText.mText = "Str ";
    mStatusAttributesPanel.mText.push_back(&mStatusStrengthText);

    fontLength = Font::GetStringFontLength(mStatusStrengthText.mText.c_str()) * TEXT_SIZE;
    mStatusStrengthValueText.mPosition = mStatusStrengthText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusStrengthValueText);

    // Defense
    mStatusDefenseText.mPosition = mStatusStrengthText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusDefenseText.mText = "Def ";
    mStatusAttributesPanel.mText.push_back(&mStatusDefenseText);

    fontLength = Font::GetStringFontLength(mStatusDefenseText.mText.c_str()) * TEXT_SIZE;
    mStatusDefenseValueText.mPosition = mStatusDefenseText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusDefenseValueText);

    // Intelligence
    mStatusIntelligenceText.mPosition = mStatusDefenseText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusIntelligenceText.mText = "Int ";
    mStatusAttributesPanel.mText.push_back(&mStatusIntelligenceText);

    fontLength = Font::GetStringFontLength(mStatusIntelligenceText.mText.c_str()) * TEXT_SIZE;
    mStatusIntelligenceValueText.mPosition = mStatusIntelligenceText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusIntelligenceValueText);

    // Speed
    mStatusSpeedText.mPosition = mStatusIntelligenceText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusSpeedText.mText = "Spd ";
    mStatusAttributesPanel.mText.push_back(&mStatusSpeedText);

    fontLength = Font::GetStringFontLength(mStatusSpeedText.mText.c_str()) * TEXT_SIZE;
    mStatusSpeedValueText.mPosition = mStatusSpeedText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusSpeedValueText);

    // Skill
    mStatusSkillText.mPosition = mStatusSpeedText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusSkillText.mText = "Skl ";
    mStatusAttributesPanel.mText.push_back(&mStatusSkillText);

    fontLength = Font::GetStringFontLength(mStatusSkillText.mText.c_str()) * TEXT_SIZE;
    mStatusSkillValueText.mPosition = mStatusSkillText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusSkillValueText);

    // Luck
    mStatusLuckText.mPosition = mStatusSkillText.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mStatusLuckText.mText = "Lck ";
    mStatusAttributesPanel.mText.push_back(&mStatusLuckText);

    fontLength = Font::GetStringFontLength(mStatusLuckText.mText.c_str()) * TEXT_SIZE;
    mStatusLuckValueText.mPosition = mStatusLuckText.mPosition + Vec2(fontLength, 0.0f);
    mStatusAttributesPanel.mText.push_back(&mStatusLuckValueText);

    SetStatusCharacterAttributes(0);
}

void MenuParty::SetupInventoryPanel()
{
    mInventoryButtonsPanel.mIsActive = false;
    mInventoryButtonsPanel.mPosition =
    {
        mMoneyPanel.mPosition.x + mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3,
        mMoneyPanel.mPosition.y
    };
    mInventoryButtonsPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
    };

    mInventoryButtonOne.mPosition = mInventoryButtonsPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mInventoryButtonTwo.mPosition = mInventoryButtonsPanel.mPosition + Vec2(mInventoryButtonsPanel.mSize.x * 0.25f, TEXT_PADDING);
    mInventoryButtonThree.mPosition = mInventoryButtonsPanel.mPosition + Vec2(mInventoryButtonsPanel.mSize.x * 0.5f, TEXT_PADDING);

    mInventoryButtonOne.OnRightAction = [this]()
    {
        mCurrentButton = &mInventoryButtonTwo;
        FillInventoryWeaponsButtons();
    };
    mInventoryButtonOne.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mInventoryButton;
    };

    mInventoryButtonTwo.OnLeftAction = [this]()
    {
        mCurrentButton = &mInventoryButtonOne;
        FillInventoryItemButtons();
    };
    mInventoryButtonTwo.OnRightAction = [this]()
    {
        mCurrentButton = &mInventoryButtonThree;
        FillInventoryArmourButtons();
    };
    mInventoryButtonTwo.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mInventoryButton;
    };

    mInventoryButtonThree.OnLeftAction = [this]()
    {
        mCurrentButton = &mInventoryButtonTwo;
        FillInventoryWeaponsButtons();
    };
    mInventoryButtonThree.OnRightAction = [this]()
    {
        
    };
    mInventoryButtonThree.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mInventoryButton;
    };

    mInventoryButtonsPanel.mButtons.push_back(&mInventoryButtonOne);
    mInventoryButtonsPanel.mButtons.push_back(&mInventoryButtonTwo);
    mInventoryButtonsPanel.mButtons.push_back(&mInventoryButtonThree);

    mInventoryPanel.mPosition =
    {
        mInventoryButtonsPanel.mPosition.x,
        mMainPanel.mPosition.y
    };
    mInventoryPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        TEXT_PADDING * 2.0f + Font::fontHeight * TEXT_SIZE * 7.0f + TEXT_PADDING * 6.0f
    };

    mInventoryPanelButtonOne.mPosition = mInventoryPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mInventoryPanelButtonTwo.mPosition = mInventoryPanel.mPosition + Vec2(mInventoryButtonsPanel.mSize.x * 0.25f, TEXT_PADDING);
    mInventoryPanelButtonThree.mPosition = mInventoryPanel.mPosition + Vec2(mInventoryButtonsPanel.mSize.x * 0.5f, TEXT_PADDING);
    mInventoryPanelButtonFour.mPosition = mInventoryPanel.mPosition + Vec2(mInventoryButtonsPanel.mSize.x * 0.75f, TEXT_PADDING);

    mInventoryPanelButtonOne.OnRightAction = [this]()
    {
        if(mInventoryPanelButtonOne.mIsActive) mCurrentButton = &mInventoryPanelButtonTwo;
    };
    mInventoryPanelButtonOne.OnAcceptAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON && PlayerManager::CanEquipWeapon(0))
        {
            mPanelState = PS_EQUIP;
            SelectPreviousButtonThird();
            PlayerManager::SetCharacterWeapon(mSelectedCharacterIndex, 0);
            FillEquipmentText(mSelectedCharacterIndex);
        }
    };
    mInventoryPanelButtonOne.OnCancelAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON)
        {
            mPanelState = PS_EQUIP;
            SelectPreviousButtonThird();
        }
    };

    mInventoryPanelButtonTwo.OnLeftAction = [this]()
    {
        if (mInventoryPanelButtonOne.mIsActive) mCurrentButton = &mInventoryPanelButtonOne;
    };
    mInventoryPanelButtonTwo.OnRightAction = [this]()
    {
        if (mInventoryPanelButtonThree.mIsActive) mCurrentButton = &mInventoryPanelButtonThree;
    };
    mInventoryPanelButtonTwo.OnAcceptAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON && PlayerManager::CanEquipWeapon(1))
        {
            mPanelState = PS_EQUIP;
            SelectPreviousButtonThird();
            PlayerManager::SetCharacterWeapon(mSelectedCharacterIndex, 1);
            FillEquipmentText(mSelectedCharacterIndex);
        }
    };
    mInventoryPanelButtonTwo.OnCancelAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON)
        {
            mPanelState = PS_EQUIP;
            SelectPreviousButtonThird();
        }
    };

    mInventoryPanelButtonThree.OnLeftAction = [this]()
    {
        if (mInventoryPanelButtonTwo.mIsActive) mCurrentButton = &mInventoryPanelButtonOne;
    };
    mInventoryPanelButtonThree.OnRightAction = [this]()
    {
        if (mInventoryPanelButtonFour.mIsActive) mCurrentButton = &mInventoryPanelButtonFour;
    };
    mInventoryPanelButtonThree.OnAcceptAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON && PlayerManager::CanEquipWeapon(2))
        {
            mPanelState = PS_EQUIP;
            mCurrentButton = mPreviousButtonSecond;
            PlayerManager::SetCharacterWeapon(mSelectedCharacterIndex, 2);
            FillEquipmentText(mSelectedCharacterIndex);
        }
    };
    mInventoryPanelButtonThree.OnCancelAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON)
        {
            mPanelState = PS_EQUIP;
            mCurrentButton = mPreviousButtonSecond;
        }
    };

    mInventoryPanelButtonFour.OnLeftAction = [this]()
    {
        if (mInventoryPanelButtonFour.mIsActive) mCurrentButton = &mInventoryPanelButtonThree;
    };
    mInventoryPanelButtonFour.OnAcceptAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON && PlayerManager::CanEquipWeapon(3))
        {
            mPanelState = PS_EQUIP;
            mCurrentButton = mPreviousButtonSecond;
            PlayerManager::SetCharacterWeapon(mSelectedCharacterIndex, 3);
            FillEquipmentText(mSelectedCharacterIndex);
        }
    };
    mInventoryPanelButtonFour.OnCancelAction = [this]()
    {
        if (mPanelState == PS_SELECTING_WEAPON)
        {
            mPanelState = PS_EQUIP;
            mCurrentButton = mPreviousButtonSecond;
        }
    };

    mInventoryPanel.mButtons.push_back(&mInventoryPanelButtonOne);
    mInventoryPanel.mButtons.push_back(&mInventoryPanelButtonTwo);
    mInventoryPanel.mButtons.push_back(&mInventoryPanelButtonThree);
    mInventoryPanel.mButtons.push_back(&mInventoryPanelButtonFour);
}

void MenuParty::SetupJournalPanel()
{
    mJournalButtonsPanel.mIsActive = false;
    mJournalButtonsPanel.mPosition =
    {
        mMoneyPanel.mPosition.x + mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3,
        mMoneyPanel.mPosition.y
    };
    mJournalButtonsPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
    };

    mJournalButtonOne.mPosition = mJournalButtonsPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mJournalButtonTwo.mPosition = mJournalButtonsPanel.mPosition + Vec2(mJournalButtonsPanel.mSize.x * 0.25f, TEXT_PADDING);
    mJournalButtonThree.mPosition = mJournalButtonsPanel.mPosition + Vec2(mJournalButtonsPanel.mSize.x * 0.5f, TEXT_PADDING);
    mJournalButtonFour.mPosition = mJournalButtonsPanel.mPosition + Vec2(mJournalButtonsPanel.mSize.x * 0.75f, TEXT_PADDING);

    mJournalButtonOne.OnRightAction = [this]()
    {
        mCurrentButton = &mJournalButtonTwo;
    };
    mJournalButtonOne.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mJournalButton;
    };

    mJournalButtonTwo.OnLeftAction = [this]()
    {
        mCurrentButton = &mJournalButtonOne;
    };
    mJournalButtonTwo.OnRightAction = [this]()
    {
        mCurrentButton = &mJournalButtonThree;
    };
    mJournalButtonTwo.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mJournalButton;
    };

    mJournalButtonThree.OnLeftAction = [this]()
    {
        mCurrentButton = &mJournalButtonTwo;
    };
    mJournalButtonThree.OnRightAction = [this]()
    {
        mCurrentButton = &mJournalButtonFour;
    };
    mJournalButtonThree.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mJournalButton;
    };

    mJournalButtonFour.OnLeftAction = [this]()
    {
        mCurrentButton = &mJournalButtonThree;
    };
    mJournalButtonFour.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mJournalButton;
    };

    mJournalButtonsPanel.mButtons.push_back(&mJournalButtonOne);
    mJournalButtonsPanel.mButtons.push_back(&mJournalButtonTwo);
    mJournalButtonsPanel.mButtons.push_back(&mJournalButtonThree);
    mJournalButtonsPanel.mButtons.push_back(&mJournalButtonFour);

    mJournalKeywordsPanel.mPosition =
    {
        mJournalButtonsPanel.mPosition.x,
        mMainPanel.mPosition.y
    };
    mJournalKeywordsPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        TEXT_PADDING * 2.0f + Font::fontHeight * TEXT_SIZE * 7.0f + TEXT_PADDING * 6.0f
    };

    mJournalKeywordsPanel.mButtons.push_back(&mKeywordsButtonOne);
    mJournalKeywordsPanel.mButtons.push_back(&mKeywordsButtonTwo);
    mJournalKeywordsPanel.mButtons.push_back(&mKeywordsButtonThree);
    mJournalKeywordsPanel.mButtons.push_back(&mKeywordsButtonFour);
}

void MenuParty::SetupEquipPanel()
{
    mEquipButtonsPanel.mIsActive = false;
    mEquipButtonsPanel.mPosition =
    {
        mMoneyPanel.mPosition.x + mMoneyPanel.mSize.x + UI_BOX_BORDER_SIZE * 3,
        mMoneyPanel.mPosition.y
    };
    mEquipButtonsPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 36.0f + Font::fontSpacing * 38.0f + TEXT_PADDING * 2.0f,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2.0f
    };

    mEquipButtonOne.mPosition = mEquipButtonsPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mEquipButtonTwo.mPosition = mEquipButtonsPanel.mPosition + Vec2(mEquipButtonsPanel.mSize.x * 0.25f, TEXT_PADDING);
    mEquipButtonThree.mPosition = mEquipButtonsPanel.mPosition + Vec2(mEquipButtonsPanel.mSize.x * 0.5f, TEXT_PADDING);
    mEquipButtonFour.mPosition = mEquipButtonsPanel.mPosition + Vec2(mEquipButtonsPanel.mSize.x * 0.75f, TEXT_PADDING);

    mEquipButtonOne.OnRightAction = [this]()
    {
        mCurrentButton = &mEquipButtonTwo;
        SetStatusCharacterAttributes(1);
        FillEquipmentText(1);
    };
    mEquipButtonOne.OnAcceptAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonEquip;
        mPreviousButtonFirst = &mEquipButtonOne;
        mSelectedCharacterIndex = 0;
    };
    mEquipButtonOne.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mEquipButton;
    };

    mEquipButtonTwo.OnLeftAction = [this]()
    {
        mCurrentButton = &mEquipButtonOne;
        SetStatusCharacterAttributes(0);
        FillEquipmentText(0);
    };
    mEquipButtonTwo.OnRightAction = [this]()
    {
        mCurrentButton = &mEquipButtonThree;
        SetStatusCharacterAttributes(2);
        FillEquipmentText(2);
    };
    mEquipButtonTwo.OnAcceptAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonEquip;
        mPreviousButtonFirst = &mEquipButtonTwo;
        mSelectedCharacterIndex = 1;
    };
    mEquipButtonTwo.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mEquipButton;
    };

    mEquipButtonThree.OnLeftAction = [this]()
    {
        mCurrentButton = &mEquipButtonTwo;
        SetStatusCharacterAttributes(1);
        FillEquipmentText(1);
    };
    mEquipButtonThree.OnRightAction = [this]()
    {
        mCurrentButton = &mEquipButtonFour;
        SetStatusCharacterAttributes(3);
        FillEquipmentText(3);
    };
    mEquipButtonThree.OnAcceptAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonEquip;
        mPreviousButtonFirst = &mEquipButtonThree;
        mSelectedCharacterIndex = 2;
    };
    mEquipButtonThree.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mEquipButton;
    };

    mEquipButtonFour.OnLeftAction = [this]()
    {
        mCurrentButton = &mEquipButtonThree;
        SetStatusCharacterAttributes(2);
        FillEquipmentText(2);
    };
    mEquipButtonFour.OnAcceptAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonEquip;
        mPreviousButtonFirst = &mEquipButtonFour;
        mSelectedCharacterIndex = 3;
    };
    mEquipButtonFour.OnCancelAction = [this]()
    {
        SetPanelState(PS_PARTY);
        mCurrentButton = &mEquipButton;
    };

    mEquipButtonsPanel.mButtons.push_back(&mEquipButtonOne);
    mEquipButtonsPanel.mButtons.push_back(&mEquipButtonTwo);
    mEquipButtonsPanel.mButtons.push_back(&mEquipButtonThree);
    mEquipButtonsPanel.mButtons.push_back(&mEquipButtonFour);

    mEquipOptionsPanel.mPosition =
    {
        mEquipButtonsPanel.mPosition.x,
        mMainPanel.mPosition.y
    };
    mEquipOptionsPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 10.0f + Font::fontSpacing * 10.0f + TEXT_PADDING * 2.0f,
        TEXT_PADDING + Font::fontHeight * TEXT_SIZE * 4.0f + TEXT_PADDING * 4.0f
    };

    mEquipOptionsButtonEquip.mPosition = mEquipOptionsPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mEquipOptionsButtonRemove.mPosition = mEquipOptionsButtonEquip.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mEquipOptionsButtonRemoveAll.mPosition = mEquipOptionsButtonRemove.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
    mEquipOptionsButtonOptimize.mPosition = mEquipOptionsButtonRemoveAll.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    mEquipOptionsButtonEquip.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonRemove;
    };
    mEquipOptionsButtonEquip.OnAcceptAction = [this]()
    {
        mCurrentButton = &mEquipmentWeaponButton;
        mPreviousButtonSecond = &mEquipOptionsButtonEquip;
        mEquipState = ES_EQUIPPING;
    };
    mEquipOptionsButtonEquip.OnCancelAction = [this]()
    {
        SelectPreviousButtonFirst();
    };

    mEquipOptionsButtonRemove.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonEquip;
    };
    mEquipOptionsButtonRemove.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonRemoveAll;
    };
    mEquipOptionsButtonRemove.OnAcceptAction = [this]()
    {
        mCurrentButton = &mEquipmentWeaponButton;
        mPreviousButtonSecond = &mEquipOptionsButtonRemove;
        mEquipState = ES_REMOVING;
    };
    mEquipOptionsButtonRemove.OnCancelAction = [this]()
    {
        SelectPreviousButtonFirst();
    };

    mEquipOptionsButtonRemoveAll.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonRemove;
    };
    mEquipOptionsButtonRemoveAll.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonOptimize;
    };
    mEquipOptionsButtonRemoveAll.OnAcceptAction = [this]()
    {
        
    };
    mEquipOptionsButtonRemoveAll.OnCancelAction = [this]()
    {
        SelectPreviousButtonFirst();
    };

    mEquipOptionsButtonOptimize.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipOptionsButtonRemoveAll;
    };
    mEquipOptionsButtonOptimize.OnAcceptAction = [this]()
    {
        
    };
    mEquipOptionsButtonOptimize.OnCancelAction = [this]()
    {
        SelectPreviousButtonFirst();
    };

    mEquipOptionsPanel.mButtons.push_back(&mEquipOptionsButtonEquip);
    mEquipOptionsPanel.mButtons.push_back(&mEquipOptionsButtonRemove);
    mEquipOptionsPanel.mButtons.push_back(&mEquipOptionsButtonRemoveAll);
    mEquipOptionsPanel.mButtons.push_back(&mEquipOptionsButtonOptimize);

    mEquipmentPanel.mPosition =
    {
        mEquipOptionsPanel.mPosition.x + mEquipOptionsPanel.mSize.x + UI_BOX_BORDER_SIZE * 3.0f,
        mMainPanel.mPosition.y
    };
    mEquipmentPanel.mSize =
    {
        Font::fontWidth * TEXT_SIZE * 23.0f + Font::fontSpacing * 23.0f + TEXT_PADDING * 2.0f,
        TEXT_PADDING * 2.0f + Font::fontHeight * TEXT_SIZE * 7.0f + TEXT_PADDING * 6.0f
    };

    float fontLength;
    float vertSpacing = Font::fontHeight * TEXT_SIZE + TEXT_PADDING;

    UIText equipmentText;
    mEquipmentWeaponButton.mPosition = mEquipmentPanel.mPosition + Vec2(TEXT_PADDING, TEXT_PADDING);
    mEquipmentWeaponButton.mText = "Wpn  ";

    fontLength = Font::GetStringFontLength(mEquipmentWeaponButton.mText.c_str()) * TEXT_SIZE;
    mEquipmentWeaponText.mPosition = mEquipmentWeaponButton.mPosition + Vec2(fontLength, 0.0f);
    mEquipmentWeaponText.mText = "";

    mEquipmentShieldButton.mPosition = mEquipmentWeaponButton.mPosition + Vec2(0.0f, vertSpacing);
    mEquipmentShieldButton.mText = "Shield  ";

    fontLength = Font::GetStringFontLength(mEquipmentShieldButton.mText.c_str()) * TEXT_SIZE;
    mEquipmentShieldText.mPosition = mEquipmentShieldButton.mPosition + Vec2(fontLength, 0.0f);
    mEquipmentShieldText.mText = "";

    mEquipmentHeadButton.mPosition = mEquipmentShieldButton.mPosition + Vec2(0.0f, vertSpacing);
    mEquipmentHeadButton.mText = "Head  ";

    fontLength = Font::GetStringFontLength(mEquipmentHeadButton.mText.c_str()) * TEXT_SIZE;
    mEquipmentHeadText.mPosition = mEquipmentHeadButton.mPosition + Vec2(fontLength, 0.0f);
    mEquipmentHeadText.mText = "";

    mEquipmentChestButton.mPosition = mEquipmentHeadButton.mPosition + Vec2(0.0f, vertSpacing);
    mEquipmentChestButton.mText = "Chest  ";

    fontLength = Font::GetStringFontLength(mEquipmentChestButton.mText.c_str()) * TEXT_SIZE;
    mEquipmentChestText.mPosition = mEquipmentChestButton.mPosition + Vec2(fontLength, 0.0f);
    mEquipmentChestText.mText = "";

    mEquipmentArmsButton.mPosition = mEquipmentChestButton.mPosition + Vec2(0.0f, vertSpacing);
    mEquipmentArmsButton.mText = "Arms  ";

    fontLength = Font::GetStringFontLength(mEquipmentArmsButton.mText.c_str()) * TEXT_SIZE;
    mEquipmentArmsText.mPosition = mEquipmentArmsButton.mPosition + Vec2(fontLength, 0.0f);
    mEquipmentArmsText.mText = "";

    mEquipmentLegsButton.mPosition = mEquipmentArmsButton.mPosition + Vec2(0.0f, vertSpacing);
    mEquipmentLegsButton.mText = "Legs  ";

    fontLength = Font::GetStringFontLength(mEquipmentLegsButton.mText.c_str()) * TEXT_SIZE;
    mEquipmentLegsText.mPosition = mEquipmentLegsButton.mPosition + Vec2(fontLength, 0.0f);
    mEquipmentLegsText.mText = "";

    mEquipmentWeaponButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipmentShieldButton;
    };
    mEquipmentWeaponButton.OnAcceptAction = [this]()
    {
        if (mEquipState == ES_EQUIPPING)
        {
            FillInventoryWeaponsButtons();
            mPanelState = PS_SELECTING_WEAPON;
            mCurrentButton = &mInventoryPanelButtonOne;
            mPreviousButtonThird = &mEquipmentWeaponButton;
        }
        else
        {
            PlayerManager::SetCharacterWeapon(mSelectedCharacterIndex, -1);
            FillEquipmentText(mSelectedCharacterIndex);
        }
    };
    mEquipmentWeaponButton.OnCancelAction = [this]()
    {
        SelectPreviousButtonSecond();
    };

    mEquipmentShieldButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipmentWeaponButton;
    };
    mEquipmentShieldButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipmentHeadButton;
    };
    mEquipmentShieldButton.OnCancelAction = [this]()
    {
        SelectPreviousButtonSecond();
    };

    mEquipmentHeadButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipmentShieldButton;
    };
    mEquipmentHeadButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipmentChestButton;
    };
    mEquipmentHeadButton.OnCancelAction = [this]()
    {
        SelectPreviousButtonSecond();
    };

    mEquipmentChestButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipmentHeadButton;
    };
    mEquipmentChestButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipmentArmsButton;
    };
    mEquipmentChestButton.OnCancelAction = [this]()
    {
        SelectPreviousButtonSecond();
    };

    mEquipmentArmsButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipmentChestButton;
    };
    mEquipmentArmsButton.OnDownAction = [this]()
    {
        mCurrentButton = &mEquipmentLegsButton;
    };
    mEquipmentArmsButton.OnCancelAction = [this]()
    {
        SelectPreviousButtonSecond();
    };

    mEquipmentLegsButton.OnUpAction = [this]()
    {
        mCurrentButton = &mEquipmentArmsButton;
    };
    mEquipmentLegsButton.OnCancelAction = [this]()
    {
        SelectPreviousButtonSecond();
    };

    mEquipmentPanel.mButtons.push_back(&mEquipmentWeaponButton);
    mEquipmentPanel.mButtons.push_back(&mEquipmentShieldButton);
    mEquipmentPanel.mButtons.push_back(&mEquipmentHeadButton);
    mEquipmentPanel.mButtons.push_back(&mEquipmentChestButton);
    mEquipmentPanel.mButtons.push_back(&mEquipmentArmsButton);
    mEquipmentPanel.mButtons.push_back(&mEquipmentLegsButton);
}

void MenuParty::SetPanelState(EPanelState state)
{
    if (state == PS_PARTY)
    {
        mStatusButtonPanel.mIsActive = true;
        mPanelState = PS_PARTY;
    }
    else mPartyPanel.mIsActive = false;

    if (state == PS_STATUS)
    {
        mStatusButtonPanel.mIsActive = true;
        mStatusAttributesPanel.mIsActive = true;
        mPanelState = PS_STATUS;
    }
    else
    {
        mStatusButtonPanel.mIsActive = false;
        mStatusAttributesPanel.mIsActive = false;
    }

    if (state == PS_JOURNAL)
    {
        mJournalButtonsPanel.mIsActive = true;
        mJournalKeywordsPanel.mIsActive = true;
        mPanelState = PS_JOURNAL;
    }
    else
    {
        mJournalButtonsPanel.mIsActive = false;
        mJournalKeywordsPanel.mIsActive = false;
    }

    if (state == PS_INVENTORY)
    {
        mInventoryButtonsPanel.mIsActive = true;
        mPanelState = PS_INVENTORY;
    }
    else
    {
        mInventoryButtonsPanel.mIsActive = false;
    }

    if (state == PS_EQUIP)
    {
        mInventoryButtonsPanel.mIsActive = true;
        mPanelState = PS_EQUIP;
    }
    else
    {
        mInventoryButtonsPanel.mIsActive = false;
    }
}

void MenuParty::FillPartyAttributes()
{
    CharacterAttributes attributes = PlayerManager::GetCharacterAttributes()[0];
    std::string string;
    UIText text;

    // First Character Button
    mPartyButtonOne.mText = attributes.characterName;

    string = "Lv." + std::to_string(attributes.level);
    mPartyLevelTextOne.mText = string;

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    mPartyClassTextOne.mText = string;

    string = std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    mPartyHPTextOne.mText = string;

    string = std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    mPartyMPTextOne.mText = string;

    // Second Character Button
    attributes = PlayerManager::GetCharacterAttributes()[1];

    mPartyButtonTwo.mText = attributes.characterName;

    string = "Lv." + std::to_string(attributes.level);
    mPartyLevelTextTwo.mText = string;

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    mPartyClassTextTwo.mText = string;

    string = std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    mPartyHPTextTwo.mText = string;

    string = std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    mPartyMPTextTwo.mText = string;

    // Third Character Button
    attributes = PlayerManager::GetCharacterAttributes()[2];

    mPartyButtonThree.mText = attributes.characterName;

    string = "Lv." + std::to_string(attributes.level);
    mPartyLevelTextThree.mText = string;

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    mPartyClassTextThree.mText = string;

    string = std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    mPartyHPTextThree.mText = string;

    string = std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    mPartyMPTextThree.mText = string;

    // Fourth Character Button
    attributes = PlayerManager::GetCharacterAttributes()[3];

    mPartyButtonFour.mText = attributes.characterName;

    string = "Lv." + std::to_string(attributes.level);
    mPartyLevelTextFour.mText = string;

    string = GetClassName(attributes.characterClass) + "  " + std::to_string(attributes.exp) + '/' + std::to_string(attributes.expNextLevel);
    mPartyClassTextFour.mText = string;

    string = std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + " HP";
    mPartyHPTextFour.mText = string;

    string = std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + " MP";
    mPartyMPTextFour.mText = string;
}

void MenuParty::SetStatusButtonsText()
{
    mStatusButtonOne.mText = PlayerManager::GetCharacterAttributes()[0].characterName;
    mStatusButtonTwo.mText = PlayerManager::GetCharacterAttributes()[1].characterName;
    mStatusButtonThree.mText = PlayerManager::GetCharacterAttributes()[2].characterName;
    mStatusButtonFour.mText = PlayerManager::GetCharacterAttributes()[3].characterName;
}

void MenuParty::SetStatusCharacterAttributes(int index)
{
    mStatusLevelValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].level);

    mStatusClassValueText.mText =
        GetClassName(PlayerManager::GetCharacterAttributes()[index].characterClass);

    mStatusHPValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].health) + " / " + std::to_string(PlayerManager::GetCharacterAttributes()[index].healthMax);

    mStatusMPValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].magicMax) + " / " + std::to_string(PlayerManager::GetCharacterAttributes()[index].magicMax);

    mStatusCurrentXPValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].exp);

    mStatusNextLevelValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].expNextLevel);

    mStatusStrengthValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].strength);

    mStatusDefenseValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].defense);
    
    mStatusIntelligenceValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].intelligence);

    mStatusSpeedValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].speed);

    mStatusSkillValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].skill);

    mStatusLuckValueText.mText =
        std::to_string(PlayerManager::GetCharacterAttributes()[index].luck);
}

void MenuParty::FillInventoryItemButtons()
{
    mInventoryPanelButtonOne.mIsActive = false;
    mInventoryPanelButtonTwo.mIsActive = false;
    mInventoryPanelButtonThree.mIsActive = false;
    mInventoryPanelButtonFour.mIsActive = false;
}

void MenuParty::FillInventoryWeaponsButtons()
{
    mInventoryPanelButtonOne.mIsActive = false;
    mInventoryPanelButtonTwo.mIsActive = false;
    mInventoryPanelButtonThree.mIsActive = false;
    mInventoryPanelButtonFour.mIsActive = false;

    for (int i = 0; i < PlayerManager::GetInventoryWeapons().size(); i++)
    {
        mInventoryPanel.mButtons[i]->mIsActive = true;
        mInventoryPanel.mButtons[i]->mText = PlayerManager::GetInventoryWeapons()[i].mName;
    }
}

void MenuParty::FillInventoryArmourButtons()
{
    mInventoryPanelButtonOne.mIsActive = false;
    mInventoryPanelButtonTwo.mIsActive = false;
    mInventoryPanelButtonThree.mIsActive = false;
    mInventoryPanelButtonFour.mIsActive = false;
}

void MenuParty::SetEquipButtonsText()
{
    mEquipButtonOne.mText = PlayerManager::GetCharacterAttributes()[0].characterName;
    mEquipButtonTwo.mText = PlayerManager::GetCharacterAttributes()[1].characterName;
    mEquipButtonThree.mText = PlayerManager::GetCharacterAttributes()[2].characterName;
    mEquipButtonFour.mText = PlayerManager::GetCharacterAttributes()[3].characterName;
}

void MenuParty::FillEquipmentText(int partyIndex)
{
    if (PlayerManager::GetCharacterWeapon(partyIndex) != -1)
    {
        mEquipmentWeaponText.mText = PlayerManager::GetInventoryWeapons()[PlayerManager::GetCharacterWeapon(partyIndex)].mName;
    }
    else
    {
        mEquipmentWeaponText.mText = "";
    }
}