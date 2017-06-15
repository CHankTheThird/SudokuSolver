#ifndef BOARD_H
#define BOARD_H

#include "Puzzle.h"
#include <string>
#include <vector>

class Board {
public:
	Board();
	Board(Puzzle* p);
	std::string printFlatLine();
	std::string printDivLine();
	std::string printBoxLine();
	std::string getLine(int line);
	std::string printBoard();
	void updateLines();
private:
	Puzzle* puz;
	std::string flatLine;
	std::string divLine;
	std::string boxLine;
	std::vector<std::string> lines;
};

#endif