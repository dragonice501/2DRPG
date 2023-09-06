#pragma once

#include "Components.h"

#include <string>
#include <fstream>

struct Enemy
{
	Enemy(const int xOffset = 0, const int yOffset = 0, const int width = 0, const int height = 0)
	{
		rect = { xOffset, yOffset, width, height };
	}

	void LoadEnemyAttributtes(const std::string& enemyName)
	{
		std::string type;
		std::string fileName = "./assets/EnemyAttributes.txt";
		std::ifstream file(fileName);
		while (file >> type)
		{
			if (type == "Name")
			{
				std::string name;
				file >> name;
				if (name == enemyName)
				{
					attributes.characterName = enemyName;
					while (file >> type)
					{
						if (type == "Health")
						{
							file >> attributes.healthMax;
							attributes.health = attributes.healthMax;
						}
						else if (type == "Magic")
						{
							file >> attributes.magicMax;
							attributes.magic = attributes.magicMax;
						}
						else if (type == "Strength") file >> attributes.strength;
						else if (type == "Defense") file >> attributes.defense;
						else if (type == "Intelligence") file >> attributes.intelligence;
						else if (type == "Speed") file >> attributes.speed;
						else if (type == "Skill") file >> attributes.skill;
						else if (type == "Luck") file >> attributes.luck;
						else if (type == "FireAffect")
						{
							int fireAffect;
							file >> fireAffect;
							this->fireAffect = static_cast<EElementAffect>(fireAffect);

							return;
						}
					}
				}
				else
				{
					for (int i = 0; i < 10; i++)
						file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}

	Vec2 position;
	SDL_Rect rect;

	CharacterAttributes attributes;
	EElementAffect fireAffect;
};