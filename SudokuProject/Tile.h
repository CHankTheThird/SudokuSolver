#ifndef TILE_H
#define TILE_H

#include <bitset>

class Tile {
public:
	Tile(int r, int c);
	Tile(int r, int c, int v);
	int getRow() { return row; }
	int getCol() { return col; }
	int getSquare() { return square; }
	int getVal() { return val; }
	bool hasVal() {
		if (val == -1) {
			return false;
		}
		else {
			return true;
		}
	}
	void setVal(int v);
	void removePotential(int v); //flips the bit of the given value to show that it can no longer be that number
	void updatePotential(int v); //called when the program has determined that only one number can go here and it needs to adjust its potential to represent that
	bool checkPotential(); //returns true if tile only has 1 potential #, false otherwise
	bool hasPotential(int v); //returns true if the tile has potential to be the given val
	int findVal(); //derives the value of the tile once it has only 1 potential left
	bool hasBeenQueued(); //returns the wasQueued bool
	void setQueueState(bool flag); //sets the wasQueued variable to flag's value (Note: should only ever be flipping to true)
private:
	bool wasQueued = false; // indicates if the tile has been added to the setQueue yet or not
	int row;	// the row the tile is in
	int col;	// the column the tile is in
	int square; // the 3x3 square the tile is in
	int val;	// the tile's value; -1 if empty
	std::bitset<9> potential;	// bitset representing the remaining potential #s for the tile 1 indicates potential, 0 indicates a number is ruled out
	int findSquare(int r, int s);	// helper function to initially determine a tile's square
};

#endif