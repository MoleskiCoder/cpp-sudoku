#include "stdafx.h"
#include "Solver.h"

#include "SudokuGrid.h"

/**
* From: https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
*
* A straightforward port from the original C to Java to C++!
*
*/

Solver::Solver(Grid<int>& start)
:	grid(start),
	width(grid.getWidth()),
	height(grid.getHeight())
{
}

/*
* Function: solve
* ---------------------
* Takes a partially filled-in grid and attempts to assign values to all
* unassigned locations in such a way to meet the requirements for sudoku
* solution (non-duplication across rows, columns, and boxes). The function
* operates via recursive backtracking: it finds an unassigned location with
* the grid and then considers all digits from 1 to 9 in a loop. If a digit
* is found that has no existing conflicts, tentatively assign it and recur
* to attempt to fill in rest of grid. If this was successful, the puzzle is
* solved. If not, unmake that decision and try again. If all digits have
* been examined and none worked out, return false to backtrack to previous
* decision point.
*/
bool Solver::solve(const int offset)
{
	if (offset == SudokuGrid::CELL_COUNT)
		return true; // success!

	const Coordinate coordinate(offset % SudokuGrid::DIMENSION, offset / SudokuGrid::DIMENSION);

	if (grid.get(coordinate) != SudokuGrid::UNASSIGNED)
		return solve(offset + 1);

	for (auto number = 0; number < SudokuGrid::DIMENSION + 1; ++number) // consider digits 1 to DIMENSION
	{
		if (isAvailable(coordinate, number)) // if looks promising,
		{
			grid.set(coordinate, number); // make tentative assignment
			if (solve(offset + 1))
			{
				return true; // recur, if success, yay!
			}
		}
	}
	grid.set(coordinate, SudokuGrid::UNASSIGNED); // failure, unmake & try again
	return false; // this triggers backtracking
}

/*
* Function: isAvailable
* ---------------------
* Returns a boolean which indicates whether it will be legal to assign
* number to the given row,column location. As assignment is legal if it that
* number is not already used in the row, column, or box.
*/
bool Solver::isAvailable(const Coordinate& coordinate, int number) const
{
	auto x = coordinate.getX();
	auto y = coordinate.getY();
	return !isUsedInRow(y, number)
		&& !isUsedInColumn(x, number)
		&& !isUsedInBox(x - x % SudokuGrid::BOX_DIMENSION, y - y % SudokuGrid::BOX_DIMENSION, number);
}

/*
* Function: isUsedInRow
* -------------------
* Returns a boolean which indicates whether any assigned entry
* in the specified row matches the given number.
*/
bool Solver::isUsedInRow(const int y, const int number) const
{
	for (auto x = 0; x < width; ++x)
	{
		if (grid.get(x, y) == number)
		{
			return true;
		}
	}
	return false;
}

/*
* Function: isUsedInColumn
* -------------------
* Returns a boolean which indicates whether any assigned entry
* in the specified column matches the given number.
*/
bool Solver::isUsedInColumn(const int x, const int number) const
{
	for (auto y = 0; y < height; ++y)
	{
		if (grid.get(x, y) == number)
		{
			return true;
		}
	}
	return false;
}

/*
* Function: isUsedInBox
* -------------------
* Returns a boolean which indicates whether any assigned entry
* within the specified BOX_DIMENSIONxBOX_DIMENSION box matches the given number.
*/
bool Solver::isUsedInBox(const int boxStartX, const int boxStartY, const int number) const
{
	for (auto y = 0; y < SudokuGrid::BOX_DIMENSION; ++y)
	{
		for (auto x = 0; x < SudokuGrid::BOX_DIMENSION; ++x)
		{
			if (grid.get(x + boxStartX, y + boxStartY) == number)
			{
				return true;
			}
		}
	}
	return false;
}
