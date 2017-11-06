#ifndef PUZZLE_H
#define PUZZLE_H

#include "Tile.h"
#include <string>
#include <vector>

/* The Puzzle class holds the 2D array of all the tiles
   and also handles the initial creation of the board.*/
class Puzzle {
public:
   // Constructors
	Puzzle();                  // Default constructor that just creates a completely empty puzzle
	Puzzle(std::string seed);  // Constructor that reads in a string of #s and Xs into a board with Xs representing blank tiles in the board

   // Getters
	std::vector<std::vector<Tile*>> getTiles() { return tiles; }

private:
	std::vector<std::vector<Tile*>> tiles;    // The two dimensional 9x9 array that holds all of the Tiles (81 in total)
};

#endif