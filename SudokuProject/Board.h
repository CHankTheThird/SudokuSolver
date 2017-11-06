#ifndef BOARD_H
#define BOARD_H

#include "Puzzle.h"
#include <string>
#include <vector>

/* The Board class is used to visually represent
   the Sudoku board in text */
class Board {
public:
   // Constructors
	Board();                         // Constructor that populates boardLines with blanks
	Board(Puzzle* puz);              // Initializes boardLines with any values provided in the given Puzzle

   // Getters
	std::string getFlatLine();
	std::string getDivLine();
	std::string getBoxLine();
	std::string getLine(int line);   // Returns the visual representation of the given row
	std::string getBoard();          // Returns the entire board representation as a string

	void updateLines();              // Regenerates boardLines to reflect the changed state of the game

private:
   std::vector<std::string> boardLines;  // The visual conversion of each row of tiles in the Sudoku board
	Puzzle* puzzle;                  // A reference to the Puzzle being solved; used for populating boardLines with tile information

	std::string flatLine = "-------------------"; // Some strings used to construct the board
	std::string divLine = "|-----|-----|-----|";
	std::string boxLine = "|=====+=====+=====|";
};

#endif