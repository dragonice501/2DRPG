#pragma once

#include "../Objects/Components.h"

#include <vector>
#include <fstream>

class PlayerManager
{
public:
	static void LoadCharacters();
	static void SaveCharacters();

private:
	static std::vector<CharacterAttributes> mCharacterAttributes;
};