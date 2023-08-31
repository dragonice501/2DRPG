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
		std::string enemy;
		std::string fileName = "./assets/EnemyAttributes.txt";
		std::ifstream file(fileName);
		while (file >> enemy)
		{
			if (enemy == enemyName)
			{
				attributes.characterName = enemyName;
				int fireAffect;

				file >>
					attributes.health >> attributes.healthMax >> attributes.magic >> attributes.magicMax >>
					attributes.strength >> attributes.defense >> attributes.intelligence >> attributes.speed >> attributes.skill >> attributes.luck >>
					fireAffect;

				this->fireAffect = static_cast<EElementAffect>(fireAffect);

				break;
			}
			else
			{
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

	size_t battleSpawnPosition;
	SDL_Rect rect;

	CharacterAttributes attributes;
	EElementAffect fireAffect;
};