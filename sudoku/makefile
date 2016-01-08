SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cc .o

CXXFLAGS += -std=c++11 -O3 -march=native

all : sudoku

Solver.o : Solver.cc

SudokuGrid.o : SudokuGrid.cc

sudoku : Solver.o SudokuGrid.o

.PHONY : clean
clean : 
	rm -fv *.exe *.o
