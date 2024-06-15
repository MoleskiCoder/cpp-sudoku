#pragma once

/**
* From: https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
*/

#include "SudokuGrid.h"

class Solver
{
private:
	SudokuGrid& grid;
	const int width;
	const int height;

public:
	Solver(SudokuGrid& start) noexcept;
	bool solve() noexcept;
	bool solve(size_t index) noexcept;

private:
	[[nodiscard]] bool isAvailable(int x, int y, int number) const noexcept;
	[[nodiscard]] bool isUsedInRow(int y, int number) const noexcept;
	[[nodiscard]] bool isUsedInColumn(int x, int number) const noexcept;
	[[nodiscard]] bool isUsedInBox(int boxStartX, int boxStartY, int number) const noexcept;
};
