#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <queue>

class Solver {
public:
	Solver(Puzzle* p);
	void updateRow(int row, int val, int sqr = -1); // update the specified row's potential except for tiles in the given square if a square is provided
	void updateCol(int col, int val, int sqr = -1); // update the specified column's potential except for tiles in the given square if a square is provided
	void updateSquare(int sqr, int val);
private:
	std::queue<Tile*> setQueue;
	std::vector<std::vector<Tile*>> tiles;
	std::vector<std::vector<int>> rowPotential; // tracks the potential of each number for each row/col - the first index corresponds to the row or col, 
	std::vector<std::vector<int>> colPotential;	// the second corresponds to a particular # value (1-9), and the value indicates the number of tiles remaining 
												// that could be that number in the row/col
	void solve();
	void setTile(Tile* tile);
	int getSquareStartRow(int sqr);
	int getSquareStartCol(int sqr);
	void checkSquare(int sqr);
	void checkAdjSquares(int sqr);
	void checkRowPotential(int r);
	void checkColPotential(int c);
	void checkBoard();
	void updateRowPotential(int r);
	void updateColPotential(int c);
};

#endif
