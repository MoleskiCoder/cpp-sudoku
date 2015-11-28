#pragma once

/**
* From: https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
*/

#include "Grid.h"

class Solver
{
private:
	Grid<int>& grid;
	int width;
	int height;

public:
	Solver(Grid<int>& start);
	bool solve();

	//Solver& operator=(const Solver& rhs)
	//{
	//	grid = rhs.grid;
	//	width = rhs.width;
	//	height = rhs.height;
	//	return *this;
	//}

private:
	bool findUnassignedLocation(Coordinate& coordinate) const;
	bool isAvailable(const Coordinate& coordinate, int number) const;
	bool isUsedInRow(int y, int number) const;
	bool isUsedInColumn(int x, int number) const;
	bool isUsedInBox(int boxStartX, int boxStartY, int number) const;
};
