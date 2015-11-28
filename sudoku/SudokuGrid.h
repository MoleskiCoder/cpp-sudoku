#pragma once

#include "Grid.h"

class SudokuGrid : public Grid<int>
{
public:
	SudokuGrid(const std::vector<int>& initial);

	std::string SudokuGrid::toString() const;

	enum
	{
		UNASSIGNED = 0,
		WIDTH = 9,
		HEIGHT = 9,
	};
};

