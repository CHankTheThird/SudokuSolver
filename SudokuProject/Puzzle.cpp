#include "Puzzle.h"

Puzzle::Puzzle() {
	for (int i = 0; i < 9; i++) {
		std::vector<Tile*> row;
		for (int j = 0; j < 9; j++) {
			Tile* tile = new Tile(i + 1, j + 1, j + 1);
			row.emplace(row.begin() + j, tile);
		}
		tiles.emplace(tiles.begin() + i, row);
	}
}

Puzzle::Puzzle(std::string seed) {
	for (int i = 0; i < 9; i++) {
		std::vector<Tile*> row;
		for (int j = 0; j < 9; j++) {
			std::string val = seed.substr(i * 9 + j, 1);
			if (val == "X") {
				Tile* tile = new Tile(i + 1, j + 1);
				row.emplace(row.begin() + j, tile);
			}
			else {
				Tile* tile = new Tile(i + 1, j + 1, std::stoi(val));
				row.emplace(row.begin() + j, tile);
			}
		}
		tiles.emplace(tiles.begin() + i, row);
	}
}