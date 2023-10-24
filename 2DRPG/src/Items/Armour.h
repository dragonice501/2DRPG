#pragma once

#include <string>
#include <fstream>

class Armour
{
public:
	Armour(const std::string& name = "")
	{
		LoadArmourAttributes(name);
	}

	std::string mName;

	int mDefense;
	int mMagicDefense;

	int mBuyCost;
	int mSellPrice;

	void LoadArmourAttributes(const std::string& weaponName)
	{
		std::string string;
		std::string fileName = "./assets/files/ArmourAttributes.txt";
		std::ifstream file(fileName);
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