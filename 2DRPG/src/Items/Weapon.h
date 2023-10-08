#pragma once

#include <string>
#include <fstream>

class Weapon
{
public:
	Weapon(const std::string& name = "")
	{
		LoadWeaponAttributes(name);
	}

	std::string mName;

	int mAttack;
	int mMagic;

	int mBuyCost;
	int mSellPrice;

	void LoadWeaponAttributes(const std::string& weaponName)
	{
		std::string string;
		std::string fileName = "./assets/WeaponAttributes.txt";
		std::ifstream file(fileName);
		while (file >> string)
		{
			if (string == "Weapon")
			{
				file >> string;
				if (string == weaponName)
				{
					mName = string;
					while (file >> string)
					{
						if (string == "Attack") file >> mAttack;
						else if (string == "Magic") file >> mMagic;
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

private:

};