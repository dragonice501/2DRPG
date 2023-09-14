#include "Font.h"

int Font::fontWidth = 5;
int Font::fontHeight = 9;
int Font::fontSpacing = 1;

std::map<char, std::array<bool, 45>> Font::fontMap =
{
	{
		'A',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
		}
	},
	{
		'B',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
		}
	},
	{
		'C',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'D',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
		}
	},
	{
		'E',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
		}
	},
	{
		'F',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
		}
	},
	{
		'G',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 1, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'H',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
		}
	},
	{
		'I',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			1, 1, 1, 1, 1,
		}
	},
	{ 
		'J',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'K',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 1, 0,
			1, 0, 1, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 0, 1, 0, 0,
			1, 0, 0, 1, 0,
			1, 0, 0, 0, 1,
		}
	},
	{
		'L',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
		}
	},
	{
		'M',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 1, 0, 1, 1,
			1, 1, 0, 1, 1,
			1, 0, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
		}
	},
	{
		'N',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 1, 0, 0, 1,
			1, 1, 0, 0, 1,
			1, 0, 1, 0, 1,
			1, 0, 1, 0, 1,
			1, 0, 0, 1, 1,
			1, 0, 0, 1, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
		}
	},
	{
		'O',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'P',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
		}
	},
	{
		'Q',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 0, 1,
			1, 0, 0, 1, 1,
			0, 1, 1, 1, 1,
		}
	},
	{
		'R',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
			1, 0, 1, 0, 0,
			1, 0, 0, 1, 0,
			1, 0, 0, 0, 1,
		}
	},
	{
		'S',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			0, 1, 1, 1, 0,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'T',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
		}
	},
	{
		'U',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'V',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 0, 1, 0,
			0, 1, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
		}
	},
	{
		'W',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 0, 1,
			1, 0, 1, 0, 1,
			1, 1, 0, 1, 1,
			1, 1, 0, 1, 1,
			1, 0, 0, 0, 1,
		}
	},
	{
		'X',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 0, 1, 0,
			0, 1, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 1, 0, 1, 0,
			0, 1, 0, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
		}
	},
	{
		'Y',
			std::array<bool, 45>
		{
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 0, 1, 0,
			0, 1, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
		}
	},
	{
		'Z',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 1, 0, 0, 0,
			0, 1, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
		}
	},
	{
		'0',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'1',
			std::array<bool, 45>
		{
			0, 1, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 1, 1, 1, 0,
		}
	},
	{
		'2',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 1, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
		}
	},
	{
		'3',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 1, 1, 0,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'4',
			std::array<bool, 45>
		{
			0, 0, 1, 1, 0,
			0, 1, 0, 1, 0,
			1, 0, 0, 1, 0,
			1, 0, 0, 1, 0,
			1, 0, 0, 1, 0,
			1, 0, 0, 1, 0,
			1, 1, 1, 1, 1,
			0, 0, 0, 1, 0,
			0, 0, 0, 1, 0,
		}
	},
	{
		'5',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 0,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			1, 1, 1, 1, 0,
		}
	},
	{
		'6',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'7',
			std::array<bool, 45>
		{
			1, 1, 1, 1, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
		}
	},
	{
		'8',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'9',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 1, 1, 1, 0,
		}
	},
	{
		'.',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
		}
	},
	{
		',',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			0, 1, 0, 0, 0,
			1, 0, 0, 0, 0,
		}
	},
	{
		';',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			0, 1, 0, 0, 0,
			1, 0, 0, 0, 0,
		}
	},
	{
		':',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			1, 1, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'\'',
			std::array<bool, 45>
		{
			0, 0, 1, 1, 0,
			0, 0, 1, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'?',
			std::array<bool, 45>
		{
			0, 1, 1, 1, 0,
			1, 0, 0, 0, 1,
			1, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
		}
	},
	{
		'!',
			std::array<bool, 45>
		{
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
		}
	},
	{
		'(',
			std::array<bool, 45>
		{
			0, 1, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
		}
	},
	{
		')',
			std::array<bool, 45>
		{
			0, 0, 0, 1, 0,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 0, 1,
			0, 0, 0, 1, 0,
		}
	},
	{
		'+',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			1, 1, 1, 1, 1,
			0, 0, 1, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'-',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'=',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
			0, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'/',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 1,
			0, 0, 0, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 1, 0,
			0, 0, 1, 0, 0,
			0, 1, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 1, 0, 0, 0,
			1, 0, 0, 0, 0,
		}
	},
	{
		'*',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 0, 1, 0, 1,
			0, 1, 1, 1, 0,
			1, 1, 1, 1, 1,
			0, 1, 1, 1, 0,
			1, 0, 1, 0, 1,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'<',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 1, 1,
			0, 1, 1, 0, 0,
			1, 0, 0, 0, 0,
			0, 1, 1, 0, 0,
			0, 0, 0, 1, 1,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
	{
		'>',
			std::array<bool, 45>
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			1, 1, 0, 0, 0,
			0, 0, 1, 1, 0,
			0, 0, 0, 0, 1,
			0, 0, 1, 1, 0,
			1, 1, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}
	},
};

int Font::GetStringFontLength(const char* string)
{
	int i = 0;
	while (string[i] != '\0')
	{
		i++;
	}
	return i * fontWidth + i * fontSpacing - 1;
}
