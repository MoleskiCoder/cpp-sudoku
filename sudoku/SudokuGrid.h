#pragma once

#include "Grid.h"

#include <vector>
#include <set>
#include <map>
#include <string>

class SudokuGrid : public Grid<int>
{
private:
	std::vector<std::set<int>> possibles;
	std::vector<int> offsets;
	size_t offsetCount;

	void clearRowPossibles(int y, int number);
	void clearColumnPossibles(int x, int number);
	void clearBoxPossibilities(int boxStartX, int boxStartY, int number);

	void eliminateAssigned();
	void eliminateDangling();

	void eliminateRowDangling();
	void eliminateColumnDangling();
	void eliminateBoxDangling();

	bool transferSingularPossibilities();

	void transferCountedEliminations(const std::map<int, std::vector<int>>& counters);
	void adjustPossibleCounters(std::map<int, std::vector<int>>& counters, int offset);

public:
	SudokuGrid(const std::vector<int>& initial);

	void eliminate();

	const std::set<int>& getPossibilities(const int offset) const
	{
		return possibles[offset];
	}

	int getOffset(size_t index) const;

	size_t getOffsetCount() const
	{
		return offsets.size();
	}

	std::string toString() const;

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

