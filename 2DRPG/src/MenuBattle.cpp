#include "MenuBattle.h"

MenuBattle::MenuBattle() :
	mFightButton("Fight"), mMagicButton("Magic"), mItemButton("Item"), mRunButton("Run")
{
	SetupActionsPanel();
	SetupPartyPanel();

	for (int i = 0; i < 6; i++)
		mSmallEnemyButtons.push_back(UIButton());
}

void MenuBattle::Render()
{
	if (mPartyActionPanel.mIsActive)
	{
		mPartyActionPanel.Render();
	}

	if (mPartyStatsPanel.mIsActive)
	{
		mPartyStatsPanel.Render();
	}
}

void MenuBattle::SetupActionsPanel()
{
	mPartyActionPanel.mIsActive = true;
	mPartyActionPanel.mPosition = { 0.70f, 0.85f };
	mPartyActionPanel.mSize =
	{
		BATTLE_MENU_WIDTH,
		TEXT_PADDING + (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 4.0f
	};

	mPartyActionPanel.mButtons.push_back(&mFightButton);
	mPartyActionPanel.mButtons.push_back(&mMagicButton);
	mPartyActionPanel.mButtons.push_back(&mItemButton);
	mPartyActionPanel.mButtons.push_back(&mRunButton);

	mFightButton.mPosition = CalcWindowPositionFromUV(mPartyActionPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mMagicButton.mPosition = mFightButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mItemButton.mPosition = mMagicButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mRunButton.mPosition = mItemButton.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
}

void MenuBattle::SetupPartyPanel()
{
	mPartyStatsPanel.mIsActive = true;
	mPartyStatsPanel.mPosition = CalcWindowPositionFromUV(mPartyActionPanel.mPosition) + Vec2(mPartyActionPanel.mSize.x + UI_BOX_BORDER_SIZE * 3, mPartyActionPanel.mPosition.y);
	mPartyStatsPanel.mPosition = CalcWindowUVFromPosition(mPartyStatsPanel.mPosition);
	mPartyStatsPanel.mSize =
	{
		BATTLE_PARTY_UI_WIDTH,
		TEXT_PADDING + (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 4.0f
	};

	mPartyNamesOne.mPosition = CalcWindowPositionFromUV(mPartyStatsPanel.mPosition) + Vec2(TEXT_PADDING, TEXT_PADDING);
	mPartyNamesTwo.mPosition = mPartyNamesOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mPartyNamesThree.mPosition = mPartyNamesTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
	mPartyNamesFour.mPosition = mPartyNamesThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	mPartyNamesOne.mText = PlayerManager::GetCharacterAttributes()[0].characterName;
	mPartyNamesTwo.mText = PlayerManager::GetCharacterAttributes()[1].characterName;
	mPartyNamesThree.mText = PlayerManager::GetCharacterAttributes()[2].characterName;
	mPartyNamesFour.mText = PlayerManager::GetCharacterAttributes()[3].characterName;

	mPartyStatsPanel.mText.push_back(&mPartyNamesOne);
	mPartyStatsPanel.mText.push_back(&mPartyNamesTwo);
	mPartyStatsPanel.mText.push_back(&mPartyNamesThree);
	mPartyStatsPanel.mText.push_back(&mPartyNamesFour);

	std::string string;

	CharacterAttributes attributes = PlayerManager::GetCharacterAttributes()[0];
	string =
		std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP" + ' ' +
		std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";
	mPartyStatsTextOne.mPosition =
		CalcWindowPositionFromUV(mPartyStatsPanel.mPosition) +
		Vec2(mPartyStatsPanel.mSize.x - Font::GetStringFontLength(string.c_str()) * TEXT_SIZE - TEXT_PADDING, TEXT_PADDING);

	attributes = PlayerManager::GetCharacterAttributes()[1];
	string =
		std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP" + ' ' +
		std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";
	mPartyStatsTextTwo.mPosition = mPartyStatsTextOne.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	attributes = PlayerManager::GetCharacterAttributes()[2];
	string =
		std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP" + ' ' +
		std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";
	mPartyStatsTextThree.mPosition = mPartyStatsTextTwo.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	attributes = PlayerManager::GetCharacterAttributes()[3];
	string =
		std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP" + ' ' +
		std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";
	mPartyStatsTextFour.mPosition = mPartyStatsTextThree.mPosition + Vec2(0.0f, Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

	mPartyStatsPanel.mText.push_back(&mPartyStatsTextOne);
	mPartyStatsPanel.mText.push_back(&mPartyStatsTextTwo);
	mPartyStatsPanel.mText.push_back(&mPartyStatsTextThree);
	mPartyStatsPanel.mText.push_back(&mPartyStatsTextFour);
}