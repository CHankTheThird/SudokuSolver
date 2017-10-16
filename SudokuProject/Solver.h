#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <queue>

class Solver {
public:
	Solver(Puzzle* p);
   // updates the specified row's potential except for tiles in the given square if a square is provided
	void updateTilePotentialInRow(int row, int val, int sqr = -1); 
   // updates the specified column's potential except for tiles in the given square if a square is provided
	void updateTilePotentialInCol(int col, int val, int sqr = -1); 
   // updates the potential for all tiles in the specified square
	void updateTilePotentialInSquare(int sqr, int val);

	//Debug-Optimization Functions
	std::string getDebugInfo();
	//----------------------------
private:
	// queue for handling tile placements one at a time
	std::queue<Tile*> setQueue;		

	// 9x9 grid = 81 tiles in 2d array
	std::vector<std::vector<Tile*>> tiles;		

	/* tracks the potential of each number for each row/col - the first index corresponds to the row or col, 
		the second corresponds to a particular # value (1-9), and the value indicates the number of tiles remaining 
		that could be that number in the row/col */
	std::vector<std::vector<int>> rowPotential; 
	std::vector<std::vector<int>> colPotential;	

	//Debug-Optimization Variables
	int setTileCalls = 0;
	int checkSquareCalls = 0;
	int checkAdjSquaresCalls = 0;
	int checkRowPotentialCalls = 0;
	int checkColPotentialCalls = 0;
	int checkBoardCalls = 0;
	int updateTilePotentialInRowCalls = 0;
	int updateTilePotentialInColCalls = 0;
	int updateTilePotentialInSqrCalls = 0;
	int updateRowPotentialCalls = 0;
	int updateColPotentialCalls = 0;
	//-------------------------------------

	void solve();
	void setTile(Tile* tile);
	int getSquareStartRow(int sqr);
	int getSquareStartCol(int sqr);
	void checkSquare(int sqr);
	void checkAdjSquares(int sqr);
	void checkRowPotential(int row);
	void checkColPotential(int col);
	void checkBoard();
	void updateRowPotential(int row);
	void updateColPotential(int col);
};

#endif
