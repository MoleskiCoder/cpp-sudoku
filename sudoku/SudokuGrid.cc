#include "stdafx.h"
#include "SudokuGrid.h"

#include <sstream>

SudokuGrid::SudokuGrid(const std::vector<int>& initial)
: Grid(WIDTH, HEIGHT, initial) {

	std::set<int> numbers;
	for (auto i = 1; i < DIMENSION + 1; ++i)
		numbers.insert(i);

	_possibles.resize(CELL_COUNT);

	for (auto offset = 0; offset < CELL_COUNT; ++offset)
		if (get(offset) == UNASSIGNED)
			_possibles[offset] = numbers;
}

void SudokuGrid::eliminate() {
	do {
		eliminateAssigned();
		eliminateDangling();
	} while (transferSingularPossibilities());
}

void SudokuGrid::createOffsets() {
	for (size_t i = 0; i < _possibles.size(); ++i)
		if (_possibles[i].size() > 1)
			_offsets.push_back(i);
	_offsetCount = _offsets.size();
}

void SudokuGrid::eliminateDangling() {
	eliminateRowDangling();
	eliminateColumnDangling();
	eliminateBoxDangling();
}

void SudokuGrid::eliminateRowDangling() {
	for (auto y = 0; y < HEIGHT; ++y) {
		auto offset = y * DIMENSION;
		std::map<int, std::vector<int>> counters;
		for (auto x = 0; x < WIDTH; ++x)
			adjustPossibleCounters(counters, offset++);
		transferCountedEliminations(counters);
	}
}

void SudokuGrid::eliminateColumnDangling() {
	for (auto x = 0; x < WIDTH; ++x) {
		auto offset = x;
		std::map<int, std::vector<int>> counters;
		for (auto y = 0; y < HEIGHT; ++y) {
			adjustPossibleCounters(counters, offset);
			offset += DIMENSION;
		}
		transferCountedEliminations(counters);
	}
}

void SudokuGrid::eliminateBoxDangling() {
	for (auto y = 0; y < HEIGHT; y += BOX_DIMENSION) {
		for (auto x = 0; x < WIDTH; x += BOX_DIMENSION) {
			std::map<int, std::vector<int>> counters;

			auto boxStartX = x - x % BOX_DIMENSION;
			auto boxStartY = y - y % BOX_DIMENSION;

			auto boxX = boxStartX;
			for (auto yOffset = 0; yOffset < BOX_DIMENSION; ++yOffset) {
				auto boxY = yOffset + boxStartY;
				auto offset = boxX + boxY * DIMENSION;
				for (auto xOffset = 0; xOffset < BOX_DIMENSION; ++xOffset)
					adjustPossibleCounters(counters, offset++);
			}
			transferCountedEliminations(counters);
		}
	}
}

void SudokuGrid::transferCountedEliminations(const std::map<int, std::vector<int>>& counters) {
	for (const auto& counter : counters) {
		if (counter.second.size() == 1) {
			const auto number = counter.first;
			const auto cell = counter.second[0];
			_possibles[cell].clear();
			_possibles[cell].insert(number);
		}
	}
}

void SudokuGrid::adjustPossibleCounters(std::map<int, std::vector<int>>& counters, const int offset) {
	for (const auto possible : _possibles[offset])
		counters[possible].push_back(offset);
}

void SudokuGrid::eliminateAssigned() {
	for (auto y = 0; y < HEIGHT; ++y) {
		for (auto x = 0; x < WIDTH; ++x) {
			const auto number = get(x, y);
			if (number != UNASSIGNED) {
				clearRowPossibles(y, number);
				clearColumnPossibles(x, number);
				clearBoxPossibilities(x - x % BOX_DIMENSION, y - y % BOX_DIMENSION, number);
			}
		}
	}
}

bool SudokuGrid::transferSingularPossibilities() {
	bool transfer = false;
	for (auto offset = 0; offset < CELL_COUNT; ++offset) {
		auto& possible = _possibles[offset];
		if (possible.size() == 1) {
			auto singular = *(possible.begin());
			set(offset, singular);
			possible.clear();
			transfer = true;
		}
	}
	return transfer;
}

void SudokuGrid::clearRowPossibles(int y, int number) {
	auto offset = y * DIMENSION;
	for (auto x = 0; x < WIDTH; ++x)
		_possibles[offset++].erase(number);
}

void SudokuGrid::clearColumnPossibles(int x, int number) {
	auto offset = x;
	for (auto y = 0; y < HEIGHT; ++y) {
		_possibles[offset].erase(number);
		offset += DIMENSION;
	}
}

void SudokuGrid::clearBoxPossibilities(int boxStartX, int boxStartY, int number) {
	auto x = boxStartX;
	for (auto yOffset = 0; yOffset < BOX_DIMENSION; ++yOffset) {
		auto y = yOffset + boxStartY;
		auto offset = x + y * DIMENSION;
		for (auto xOffset = 0; xOffset < BOX_DIMENSION; ++xOffset)
			_possibles[offset++].erase(number);
	}
}

std::string SudokuGrid::toString() const {
	std::ostringstream output;
	for (auto y = 0; y < HEIGHT; ++y) {
		output << std::endl;
		for (auto x = 0; x < WIDTH; ++x) {
			auto number = get(x, y);
			output << ' ';
			if (number == UNASSIGNED) {
				output << '-';
			} else {
				output << std::hex << number;
			}
			output << ' ';
			if ((x + 1) % BOX_DIMENSION == 0 && (x + 1) < WIDTH) {
				output << '|';
			}
		}
		if ((y + 1) % BOX_DIMENSION == 0 && (y + 1) < HEIGHT) {
			output << std::endl <<  " --------+---------+--------";
		}
		output << std::endl;
	}
	return output.str();
}
