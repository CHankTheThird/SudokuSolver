#include "Board.h"
#include "Puzzle.h"
#include "Solver.h"
#include <iostream>

int main() {
	Puzzle *easy = new Puzzle("82XXXXX464X1XXX5X2X6X2X4X1XXX6X4X9XXXXX3X8XXXXX7X6X1XXX1X8X7X5X9X3XXX4X165XXXXX97");
	Puzzle *medium = new Puzzle("8XX3X9XX613XXXXX78XXXXXXXXX3XXXXXXX5XX7XXX6XXX425X198XXXX9X3XXXX1X7X4X3X9XX2X8XX4");
	Puzzle *hard = new Puzzle("XXX8X74XXXXXXXXX9X59XX3XXXX7X6XXXXX5XXX3X4XXX3X5XXXXX182XX1XXXXXXXXXXX6XXXX4X95XX");
	Puzzle *curr;
	std::cout << "Welcome to the Sudoku Solver" << std::endl;
	std::string puzz = "";
	while (puzz != "easy" && puzz != "medium" && puzz != "hard") {
		std::cout << "Please indicate which level of difficulty puzzle\nyou would like to see solved? (easy, medium, hard)" << std::endl;
		std::cin >> puzz;
	}
	if (puzz == "easy") {
		curr = easy;
	}
	else if (puzz == "medium") {
		curr = medium;
	}
	else {
		curr = hard;
	}
	Board board(curr);
	std::cout << board.printBoard();
	Solver s(curr);
	board.updateLines();
	std::cout << board.printBoard();
	while (puzz != "exit") {
		std::cout << "Type exit to close program" << std::endl;
		std::cin >> puzz;
	}
	return 1;
}