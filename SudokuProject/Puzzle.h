#ifndef PUZZLE_H
#define PUZZLE_H

#include "Tile.h"
#include <string>
#include <vector>

class Puzzle {
public:
	Puzzle();
	Puzzle(std::string seed);
	std::vector<std::vector<Tile*>> getTiles() { return tiles; }
private:
	std::vector<std::vector<Tile*>> tiles;
};

#endif