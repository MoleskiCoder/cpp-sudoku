#pragma once

#include "Grid.h"

#include <vector>
#include <set>
#include <map>
#include <string>

class SudokuGrid final : public Grid<int> {
private:
	std::vector<std::set<int>> _possibles;
	std::vector<int> _offsets;
	size_t _offsetCount;

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
	void createOffsets();

	[[nodiscard]] constexpr const auto& possibilities(const int offset) const noexcept {
		return _possibles[offset];
	}

	[[nodiscard]] constexpr auto offset(const size_t index) const noexcept {
		if (index + 1 > _offsetCount)
			return -1;
		return _offsets[index];
	}

	[[nodiscard]] constexpr auto offsetCount() const noexcept {
		return _offsetCount;
	}

	[[nodiscard]] std::string toString() const;

	enum {
		UNASSIGNED = 0,
		DIMENSION = 9,
		CELL_COUNT = DIMENSION * DIMENSION,
		WIDTH = DIMENSION,
		HEIGHT = DIMENSION,
		BOX_DIMENSION = 3
	};
};

