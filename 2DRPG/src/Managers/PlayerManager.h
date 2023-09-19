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
	static const std::vector<std::string>& GetLearnedKeywords() { return mLearnedKeywords; }
	static const int GetPartyMoney() { return mPartyMoney; }

	static void LearnNewKeyword(const std::string& keyword) { mLearnedKeywords.push_back(keyword); }

private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
	static std::vector<SDL_Texture*> mCharacterTextures;
	static std::vector<std::string> mLearnedKeywords;

	static int mPartyMoney;
};