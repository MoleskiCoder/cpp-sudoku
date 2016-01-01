#pragma once

/**
* From: https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
*/

#include "SudokuGrid.h"

class Solver
{
private:
	SudokuGrid& grid;
	int width;
	int height;

public:
	Solver(SudokuGrid& start);
	bool solve();
	bool solve(size_t index);

private:
	bool isAvailable(int x, int y, int number) const;
	bool isUsedInRow(int y, int number) const;
	bool isUsedInColumn(int x, int number) const;
	bool isUsedInBox(int boxStartX, int boxStartY, int number) const;
};
