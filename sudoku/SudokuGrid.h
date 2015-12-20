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
		DIMENSION = 9,
		CELL_COUNT = DIMENSION * DIMENSION,
		WIDTH = DIMENSION,
		HEIGHT = DIMENSION,
		BOX_DIMENSION = 3
	};
};

