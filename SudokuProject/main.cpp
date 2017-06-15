#include "Board.h"
#include "Puzzle.h"
#include "Solver.h"
#include <iostream>

int main() {
	Puzzle *p = new Puzzle("82XXXXX464X1XXX5X2X6X2X4X1XXX6X4X9XXXXX3X8XXXXX7X6X1XXX1X8X7X5X9X3XXX4X165XXXXX97");
	Puzzle *hard = new Puzzle("8XX3X9XX613XXXXX78XXXXXXXXX3XXXXXXX5XX7XXX6XXX425X198XXXX9X3XXXX1X7X4X3X9XX2X8XX4");
	Puzzle *hardest = new Puzzle("XXXX9X7XXX198XXX6X3XXXX2X9XXX29X3X8X5XXXXXXX3X9X4X16XXX3X2XXXX9X7XXX914XXX8X7XXXX");
	Board board(hardest);
	std::cout << board.printBoard();
	Solver s(hardest);
	board.updateLines();
	std::cout << board.printBoard();
	while (true) {
	}
	return 1;
}