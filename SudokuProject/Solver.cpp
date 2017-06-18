#include "Solver.h"

//just for testing
#include <iostream>

Solver::Solver(Puzzle* p) {
	tiles = p->getTiles();
	rowPotential.resize(9);
	colPotential.resize(9);
	for (int k = 0; k < 9; k++) {
		rowPotential[k].resize(9);
		colPotential[k].resize(9);
		for (int h = 0; h < 9; h++) {
			rowPotential[k][h] = 9;
			colPotential[k][h] = 9;
		}
	}
	//initial updating
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tiles[i][j]->hasVal()) {
				int val = tiles[i][j]->getVal();
				rowPotential[i][val-1] = 0;
				updateRowPotential(i);
				colPotential[j][val-1] = 0;
				updateColPotential(j);
				updateCol(j, val);
				updateRow(i, val);
				updateSquare(tiles[i][j]->getSquare(), val);
				tiles[i][j]->setQueueState(true);
			}
		}
	}
	checkBoard();
	//std::cout << "Tiles to set after initial updates called: " << setQueue.size() << std::endl;
}

void Solver::checkBoard() {
	for (int i = 1; i < 10; i++) {
		checkSquare(i);
		checkRowPotential(i - 1);
		checkColPotential(i - 1);
	}
	if (!setQueue.empty()) {
		solve();
	}
}

void Solver::solve() {
	int count = 1;
	while (!setQueue.empty()) {
		Tile* tile = setQueue.front();
		setTile(tile);
		std::cout << "Step " << count << ": Placed " << tile->getVal() << " at " << tile->getRow() << ", " << tile->getCol() << std::endl;
		setQueue.pop();
		count++;
	}
	checkBoard();
	count = count;
}

void Solver::setTile(Tile* tile) {
	tile->setVal(tile->findVal());
	int v = tile->getVal();
	int r = tile->getRow();
	int c = tile->getCol();
	rowPotential[r-1][v - 1] = 0;
	colPotential[c-1][v - 1] = 0;
	updateRowPotential(r - 1);
	updateColPotential(c - 1);
	updateCol(c-1, v);
	updateRow(r-1, v);
	updateSquare(tile->getSquare(), v);
	checkAdjSquares(tile->getSquare());
}

void Solver::updateRow(int row, int val, int sqr) {
	//loop through tiles in row and update potential
	for (int i = 0; i < 9; i++) {
		if (!tiles[row][i]->hasVal() && !tiles[row][i]->checkPotential() && tiles[row][i]->getSquare() != sqr) {
			if (tiles[row][i]->hasPotential(val)) {
				colPotential[i][val - 1]--;
				tiles[row][i]->removePotential(val);
			}
			if (tiles[row][i]->checkPotential() && !tiles[row][i]->hasBeenQueued()) {
				setQueue.push(tiles[row][i]);
				tiles[row][i]->setQueueState(true);
			}
		}
	}
}

void Solver::updateCol(int col, int val, int sqr) {
	//loop through tiles in column and update potential
	for (int i = 0; i < 9; i++) {
		if (!tiles[i][col]->hasVal() && !tiles[i][col]->checkPotential() && tiles[i][col]->getSquare() != sqr) {
			if (tiles[i][col]->hasPotential(val)) {
				rowPotential[i][val - 1]--;
				tiles[i][col]->removePotential(val);
			}
			if (tiles[i][col]->checkPotential() && !tiles[i][col]->hasBeenQueued()) {
				setQueue.push(tiles[i][col]);
				tiles[i][col]->setQueueState(true);
			}
		}
	}
}

void Solver::updateSquare(int sqr, int val) {
	//determine the starting row and col of the square
	int r = getSquareStartRow(sqr);
	int c = getSquareStartCol(sqr);
	//loop through tiles in square and update potential
	for (int i = r; i < r + 3; i++) {
		for (int j = c; j < c + 3; j++) {
			if (!tiles[i][j]->hasVal() && !tiles[i][j]->checkPotential()) {
				if (tiles[i][j]->hasPotential(val)) {
					rowPotential[i][val - 1]--;
					colPotential[j][val - 1]--;
					tiles[i][j]->removePotential(val);
				}
				if (tiles[i][j]->checkPotential() && !tiles[i][j]->hasBeenQueued()) {
					setQueue.push(tiles[i][j]);
					tiles[i][j]->setQueueState(true);
				}
			}
		}
	}
}

int Solver::getSquareStartRow(int sqr) {
	int r = -1;
	if (sqr < 4) {
		r = 0;
	}
	else if (sqr > 3 && sqr < 7) {
		r = 3;
	}
	else if (sqr > 6) {
		r = 6;
	}
	return r;
}

int Solver::getSquareStartCol(int sqr) {
	int c = -1;
	if (sqr % 3 == 1) {
		c = 0;
	}
	else if (sqr % 3 == 2) {
		c = 3;
	}
	else if (sqr % 3 == 0) {
		c = 6;
	}
	return c;
}

/* Need a way to check scenario in which only one tile in a square
   can be a specific number and place a tile accordingly */
void Solver::checkSquare(int sqr) {
	int r = getSquareStartRow(sqr);
	int c = getSquareStartCol(sqr);
	// loop through the tiles in the square; if for all tiles, only one shows potential for a certain #, then add it to the setQueue
	int count = 0;
	int val = 1;
	while (val < 10) {
		int refr = -1;
		int refc = -1;
		for (int i = r; i < r + 3; i++) {
			for (int j = c; j < c + 3; j++) {
				if (!tiles[i][j]->hasVal()) {
					if (tiles[i][j]->hasPotential(val)) {
						count++;
						refr = i;
						refc = j;
					}
				}
			}
		}
		if (count == 1) {
			if (!tiles[refr][refc]->hasBeenQueued()) {
				tiles[refr][refc]->updatePotential(val);
				setQueue.push(tiles[refr][refc]);
				tiles[refr][refc]->setQueueState(true);
			}
		}
		else if (count == 2 || count == 3) {
			/* if a specific # only has 2 or 3 potential tiles and they are all in the same row or col
			   then we can remove that potential from all tiles in that row or col outside that square */
			int alignedR = 0;
			int alignedC = 0;
			for (int i = 0; i < 3; i++) {
				if (tiles[refr][c + i]->hasPotential(val)) {
					alignedR++;
				}
				if (tiles[r + i][refc]->hasPotential(val)) {
					alignedC++;
				}
			}
			if (alignedR == count) {
				updateRow(refr, val, sqr);
			}
			else if (alignedC == count) {
				updateCol(refc, val, sqr);
			}
		}
		val++;
		count = 0;
	}
}

/* This calls checkSquare on the squares that are in the same row and col as the
   square that just had a tile set with a number (Note: this means the squares
   are not necessarily adjacent) */
void Solver::checkAdjSquares(int sqr) {
	int r = getSquareStartRow(sqr);
	int c = getSquareStartCol(sqr);
	int radj = 1;
	int cadj = 1;
	if (r == 3) {
		radj = 4;
	}
	else if (r == 6) {
		radj = 7;
	}
	if (c == 3) {
		cadj = 2;
	}
	else if (c == 6) {
		cadj = 3;
	}
	for (int i = 0; i < 3; i++) {
		if (cadj + i * 3 != sqr) {
			checkSquare(cadj + i * 3);
		}
		if (radj + i != sqr) {
			checkSquare(radj + i);
		}
	}
}

void Solver::checkRowPotential(int r) {
	for (int j = 0; j < 9; j++) {
		if (rowPotential[r][j] == 1) {
			for (int k = 0; k < 9; k++) {
				if (tiles[r][k]->hasPotential(j + 1) && !tiles[r][k]->hasBeenQueued()) {
					setQueue.push(tiles[r][k]);
					tiles[r][k]->setQueueState(true);
					tiles[r][k]->updatePotential(j + 1);
				}
			}
		}
	}
}

void Solver::checkColPotential(int c) {
	for (int j = 0; j < 9; j++) {
		if (colPotential[c][j] == 1) {
			for (int k = 0; k < 9; k++) {
				if (tiles[k][c]->hasPotential(j + 1) && !tiles[k][c]->hasBeenQueued()) {
					setQueue.push(tiles[k][c]);
					tiles[k][c]->setQueueState(true);
					tiles[k][c]->updatePotential(j + 1);
				}
			}
		}
	}
}

void Solver::updateRowPotential(int r) {
	for (int i = 0; i < 9; i++) {
		if (rowPotential[r][i] > 1) {
			rowPotential[r][i]--;
		}
	}
}

void Solver::updateColPotential(int c) {
	for (int i = 0; i < 9; i++) {
		if (colPotential[i][c] > 1) {
			colPotential[i][c]--;
		}
	}
}