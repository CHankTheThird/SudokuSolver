#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.h"
#include <queue>

/* The Solver class performs takes in a Puzzle and performs
   all the logic necessary to determine where numbers should 
   be placed within the board. Tracks Row, Column, and Square
   information needed for logic as well */
class Solver {
public:
   // Constructors
	Solver(Puzzle* p);      // Reads in the tile information from given Puzzle and adds all tiles with values to the setQueue; calls checkboard to begin solving

	//Debug-Optimization Functions
	std::string getDebugInfo();
	
private:
	// queue for handling tile placements one at a time
	std::queue<Tile*> setQueue;		

	/* 9x9 grid = 81 tiles in 2d array
      Note: if more information was stored in the Puzzle
      class we would probably keep a reference to the
      Puzzle and would get the tiles from it when needed */
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

   // Tile Setting and Queueing
	void solve();                       // main program loop; checks if there are any tiles to be placed, places tiles, and updates board state
	void setTile(Tile* tile);           // places tile and updates the row, column, and square information relevant to the placed tile

   // Potential-checking
   void checkBoard();                  // calls corresponding check functions on all rows, columns, and squares to determine if board is solved; calls solve if unfinished
	void checkSquare(int sqr);          // checks if only one tile in a given square can be a certain # and if so queues it; also checks for inline potential
	void checkAdjSquares(int sqr);      // calls checkSquare on squares in same starting row or column as given square
	void checkRowPotential(int row);    // checks if any # value only has one tile with that potential in the given row/column and queues accordingly
	void checkColPotential(int col);

   // Updates
   void updateTilePotentialInRow(int row, int val, int sqr = -1); // updates the tile potential in the given row/column except for tiles in sqr if one is given
   void updateTilePotentialInCol(int col, int val, int sqr = -1);
   void updateTilePotentialInSquare(int sqr, int val);            // updates the potential for all tiles in the specified square
	void updateRowPotential(int row);   // called when a tile is placed; informs the row/column that there is now one less possible tile for all # values
	void updateColPotential(int col);
   
   // Helpers
   int getSquareStartRow(int sqr);     // helper functions that find the row and column # at the top left corner of a given square
   int getSquareStartCol(int sqr);
};

#endif
