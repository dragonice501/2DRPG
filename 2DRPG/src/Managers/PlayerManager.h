#pragma once

#include "../Objects/Components.h"

#include "../Managers/GraphicsManager.h"

#include <vector>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

class PlayerManager
{
public:
	static void LoadCharacters();
	static void SaveCharacters();

	static std::vector<CharacterAttributes>& GetCharacterAttributes() { return mCharacterAttributes; }
	static const std::vector<SDL_Texture*>& GetCharacterTextures() { return mCharacterTextures; }
	static const int GetPartyMoney() { return mPartyMoney; }
	static const std::vector<std::string>& GetPeopleKeywords() { return mPeopleKeywords; }
	static const std::vector<std::string>& GetPlacesKeywords() { return mPlacesKeywords; }
	static const std::vector<std::string>& GetMysteryKeywords() { return mMysteryKeywords; }
	static const std::vector<std::string>& GetBestiaryKeywords() { return mBestiaryKeywords; }

	static void LearnNewKeyword(const std::string& keyword) { mLearnedKeywords.push_back(keyword); }

	static void LearnNewPeopleKeyword(const std::string& keyword) { mPeopleKeywords.push_back(keyword); }
	static void LearnNewPlaceKeyword(const std::string& keyword) { mPlacesKeywords.push_back(keyword); }
	static void LearnNewMysteryKeyword(const std::string& keyword) { mMysteryKeywords.push_back(keyword); }
	static void LearnNewBestiaryKeyword(const std::string& keyword) { mBestiaryKeywords.push_back(keyword); }

	static int CalcLevelUpExp(int level);
	static bool CheckLevelUp(int& outIndex);
	static void LevelUp(int characterIndex);

private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
	static std::vector<SDL_Texture*> mCharacterTextures;
	static std::vector<std::string> mLearnedKeywords;

	static std::vector<std::string> mPeopleKeywords;
	static std::vector<std::string> mPlacesKeywords;
	static std::vector<std::string> mMysteryKeywords;
	static std::vector<std::string> mBestiaryKeywords;

	static int mPartyMoney;

	static int mLevelExpAmounts[];
};