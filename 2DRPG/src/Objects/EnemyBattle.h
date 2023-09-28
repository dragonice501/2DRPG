#pragma once

#include "CharacterBattle.h"

#include <string>

class EnemyBattle : public ActorBattle
{
public:
	EnemyBattle() {}
	~EnemyBattle() {}

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
						if (type == "Level") file >> attributes.level;
						else if (type == "Health")
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
					for (int i = 0; i < 11; i++)
						file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}

	int mEnemyPositionIndex;
};