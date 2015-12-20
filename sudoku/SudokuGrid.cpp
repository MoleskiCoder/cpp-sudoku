#include "stdafx.h"
#include "SudokuGrid.h"

#include <string>

SudokuGrid::SudokuGrid(const std::vector<int>& initial)
: Grid(WIDTH, HEIGHT, initial)
{
}

std::string SudokuGrid::toString() const
{
	std::string output;
	for (auto y = 0; y < HEIGHT; ++y)
	{
		output += "\n";
		for (auto x = 0; x < WIDTH; ++x)
		{
			auto number = get(x, y);
			output += ' ';
			if (number == UNASSIGNED)
			{
				output += '-';
			}
			else
			{
				output += std::to_string(number);
			}
			output += ' ';
			if ((x + 1) % BOX_DIMENSION == 0 && (x + 1) < WIDTH)
			{
				output += '|';
			}
		}
		if ((y + 1) % BOX_DIMENSION == 0 && (y + 1) < HEIGHT)
		{
			output += "\n --------+---------+--------";
		}
		output += '\n';
	}
	return output;
}

