#pragma once

#include <string>
#include <fstream>
#include <SDL.h>

class Armour
{
public:
	enum EArmourType
	{
		HEAD,
		CHEST,
		ARMS,
		LEGS
	};

	Armour(const std::string& name = "")
	{
		LoadArmourAttributes(name);
	}

	std::string mName;
	EArmourType mArmourType;
	int mDefense;
	int mMagicDefense;

	int mBuyCost;
	int mSellPrice;

	void LoadArmourAttributes(const std::string& weaponName)
	{
		std::string string;
		std::string basePath = SDL_GetBasePath();
		std::string filePath = "assets\\files\\ArmourAttributes.txt";
		std::ifstream file(basePath + filePath);
		while (file >> string)
		{
			if (string == "Armour")
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
						else if (string == "Type")
						{
							int type;
							file >> type;

							mArmourType = static_cast<EArmourType>(type);
						}
						else if (string == "MagicDefense") file >> mMagicDefense;
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
					for (int i = 0; i < 4; i++)
						file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}
};