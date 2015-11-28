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
	for (auto y = 0; y < getHeight(); ++y)
	{
		output += "\n";
		for (auto x = 0; x < getWidth(); ++x)
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
			if ((x + 1) % 3 == 0 && (x + 1) < getWidth())
			{
				output += '|';
			}
		}
		if ((y + 1) % 3 == 0 && (y + 1) < getHeight())
		{
			output += "\n --------+---------+--------";
		}
		output += '\n';
	}
	return output;
}

