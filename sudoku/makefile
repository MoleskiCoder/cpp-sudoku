all : sudoku.exe

Solver.o : Solver.cpp
	g++ -std=c++11 -c -o Solver.o Solver.cpp

SudokuGrid.o : SudokuGrid.cpp
	g++ -std=c++11 -c -o SudokuGrid.o SudokuGrid.cpp

sudoku.o : sudoku.cpp
	g++ -std=c++11 -c -o sudoku.o sudoku.cpp

sudoku.exe : sudoku.o Solver.o SudokuGrid.o
	g++ sudoku.o Solver.o SudokuGrid.o -o sudoku.exe

.PHONY : clean
clean : 
	rm -fv *.exe *.o
