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

	static const std::vector<CharacterAttributes>& GetCharacterAttributes() { return mCharacterAttributes; }
	static const std::vector<ECharacterClass>& GetChacterClasses() { return mCharacterClasses; }
	static const std::vector<SDL_Texture*>& GetCharacterTextures() { return mCharacterTextures; }

private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
	static std::vector<ECharacterClass> mCharacterClasses;
	static std::vector<SDL_Texture*> mCharacterTextures;
};