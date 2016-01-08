#include "stdafx.h"

#include "SudokuGrid.h"
#include "Solver.h"

#include <vector>
#include <ctime>
#include <iostream>

int main()
{
	// http://www.telegraph.co.uk/news/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html
	std::vector<int> data =
	{
		8, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 3, 6, 0, 0, 0, 0, 0,
		0, 7, 0, 0, 9, 0, 2, 0, 0,
		0, 5, 0, 0, 0, 7, 0, 0, 0,
		0, 0, 0, 0, 4, 5, 7, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 3, 0,
		0, 0, 1, 0, 0, 0, 0, 6, 8,
		0, 0, 8, 5, 0, 0, 0, 1, 0,
		0, 9, 0, 0, 0, 0, 4, 0, 0
	};

	auto puzzle = SudokuGrid(data);
	auto solver = Solver(puzzle);

	auto start = std::clock();
	bool solved = solver.solve();
	auto finish = std::clock();

	if (solved)
	{
		std::cout << puzzle.toString().c_str();

		auto elapsed = finish - start;
		auto seconds = (elapsed % CLOCKS_PER_SEC) / double(CLOCKS_PER_SEC) + (elapsed / CLOCKS_PER_SEC);

		std::cout << std::endl << std::endl << "Time taken " << seconds << std::endl;
	}
	else
	{
		std::cout << "No solution exists" << std::endl;
	}

	return 0;
}
