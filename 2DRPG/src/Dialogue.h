#pragma once

#include <vector>
#include <string>

struct Dialogue
{
	Dialogue(std::vector<std::string> dialogue)
	{
		this->dialoge = dialoge;
	}

	std::vector<std::string> dialoge;
	std::string keyWord;
	std::string storylineFlag;
};