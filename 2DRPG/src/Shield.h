#pragma once

#include <string>
#include <fstream>
#include <SDL.h>

class Shield
{
public:
	Shield(const std::string& name = "")
	{
		LoadShieldAttributes(name);
	}

	std::string mName;
	int mDefense;
	int mMagicDefense;
	int mEvasion;

	int mBuyCost;
	int mSellPrice;

	void LoadShieldAttributes(const std::string& weaponName)
	{
		std::string string;
		std::string basePath = SDL_GetBasePath();
		std::string filePath = "assets\\files\\ShieldAttributes.txt";
		std::ifstream file(basePath + filePath);
		while (file >> string)
		{
			if (string == "Shield")
			{
				file >> string;
				if (string == weaponName)
				{
					mName = string;
					for (char& c : mName)
					{
						if (c == '-')
						{
							c = ' ';
							break;
						}
					}

					while (file >> string)
					{
						if (string == "Defense") file >> mDefense;
						else if (string == "MagicDefense") file >> mMagicDefense;
						else if (string == "Evasion") file >> mEvasion;
						else if (string == "Buy") file >> mBuyCost;
						else if (string == "Sell")
						{
							file >> mSellPrice;
							return;
						}
					}
				}
				else
				{
					for (int i = 0; i < 5; i++)
						file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}
};