#include "stdafx.h"
#include "Solver.h"

/**
* From: https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
*
*/

Solver::Solver(SudokuGrid& start)
:	grid(start),
	width(grid.getWidth()),
	height(grid.getHeight())
{
}

bool Solver::solve()
{
	grid.eliminate();
	grid.createOffsets();
	return solve(0);
}

/*
* Function: solve
* ---------------
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
bool Solver::solve(const size_t index)
{
	auto offset = grid.getOffset(index);

	if (offset == -1)
		return true; // success!

	const auto& numbers = grid.getPossibilities(offset);

	auto x = offset % SudokuGrid::DIMENSION;
	auto y = offset / SudokuGrid::DIMENSION;

	for (auto number : numbers)
	{
		if (isAvailable(x, y, number)) // if looks promising,
		{
			grid.set(offset, number); // make tentative assignment
			if (solve(index + 1))
			{
				return true; // recur, if success, yay!
			}
		}
	}
	grid.set(offset, SudokuGrid::UNASSIGNED); // failure, unmake & try again
	return false; // this triggers backtracking
}

/*
* Function: isAvailable
* ---------------------
* Returns a boolean which indicates whether it will be legal to assign
* number to the given row,column location. As assignment is legal if it that
* number is not already used in the row, column, or box.
*/
bool Solver::isAvailable(int x, int y, int number) const
{
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
	auto offset = y * SudokuGrid::DIMENSION;
	for (auto x = 0; x < width; ++x)
	{
		if (grid.get(offset++) == number)
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
	auto offset = x;
	for (auto y = 0; y < height; ++y)
	{
		if (grid.get(offset) == number)
		{
			return true;
		}
		offset += SudokuGrid::DIMENSION;
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
	auto x = boxStartX;
	for (auto yOffset = 0; yOffset < SudokuGrid::BOX_DIMENSION; ++yOffset)
	{
		auto y = yOffset + boxStartY;
		auto offset = x + y*SudokuGrid::DIMENSION;
		for (auto xOffset = 0; xOffset < SudokuGrid::BOX_DIMENSION; ++xOffset)
		{
			if (grid.get(offset++) == number)
			{
				return true;
			}
		}
	}
	return false;
}
