#ifndef TILE_H
#define TILE_H

#include <bitset>

/* Tiles are the most basic element of the Sudoku board.
   They contain their own location, potential, and queue
   state information. */
class Tile {
public:
   // Constructors
	Tile(int row, int col);          // Creates tile at given row and column with no value assigned (-1)
	Tile(int row, int col, int val); // Creates tile at given row and column with provided value

   // Getters
	int getRow() { return row; }
	int getCol() { return col; }
	int getSquare() { return square; }
	int getVal() { return val; }
   bool hasVal();                   // returns true if the tile has been assigned a value, false otherwise (val == -1)

   // Value functions
   int findVal();                   // derives the value of the tile once it has only 1 potential left
	void setVal(int val);            // sets the value of the tile to val

   // Potential functions
	void removePotential(int val);   // flips the bit of the given value to show that it can no longer be that number
	void setPotentialAs(int val);    // called when the program has determined that only one number can be in this tile and adjusts its potential to represent that
	bool hasSinglePotential();       // returns true if tile only has one potential number, false otherwise
	bool hasPotential(int val);      // returns true if the tile has potential to be the given value

   // Queue functions
	bool hasBeenQueued();            // returns the wasQueued bool
	void setQueueState(bool flag);   // sets the wasQueued variable to flag's value (Note: should only ever be flipping to true)


private:
	bool wasQueued = false;          // indicates if the tile has been added to the queue of tiles to be placed yet or not
	int row;	                        // the row the tile is in
	int col;	                        // the column the tile is in
	int square;                      // the 3x3 square the tile is in
	int val;	                        // the tile's value; -1 if empty
	std::bitset<9> potential;	      // bitset representing the remaining potential #s for the tile; 1 indicates potential, 0 indicates a number is ruled out
	int findSquare(int r, int s);	   // helper function to initially determine a tile's square
};

#endif