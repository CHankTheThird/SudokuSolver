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
				updateTilePotentialInCol(j, val);
				updateTilePotentialInRow(i, val);
				updateTilePotentialInSquare(tiles[i][j]->getSquare(), val);
				tiles[i][j]->setQueueState(true);
			}
		}
	}
	checkBoard();
	//std::cout << "Tiles to set after initial updates called: " << setQueue.size() << std::endl;
}

void Solver::checkBoard() {
	checkBoardCalls++;

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
	setTileCalls++;

	tile->setVal(tile->findVal());
	int v = tile->getVal();
	int r = tile->getRow();
	int c = tile->getCol();
	rowPotential[r - 1][v - 1] = 0;
	colPotential[c - 1][v - 1] = 0;
	updateRowPotential(r - 1);
	updateColPotential(c - 1);
	updateTilePotentialInCol(c - 1, v);
	updateTilePotentialInRow(r - 1, v);
	updateTilePotentialInSquare(tile->getSquare(), v);
}

void Solver::updateTilePotentialInRow(int row, int val, int sqr) {
	updateTilePotentialInRowCalls++;

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

void Solver::updateTilePotentialInCol(int col, int val, int sqr) {
	updateTilePotentialInColCalls++;

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

void Solver::updateTilePotentialInSquare(int sqr, int val) {
	updateTilePotentialInSqrCalls++;

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
	int row = -1;
	if (sqr < 4) {
		row = 0;
	}
	else if (sqr > 3 && sqr < 7) {
		row = 3;
	}
	else if (sqr > 6) {
		row = 6;
	}
	return row;
}

int Solver::getSquareStartCol(int sqr) {
	int col = -1;
	if (sqr % 3 == 1) {
		col = 0;
	}
	else if (sqr % 3 == 2) {
		col = 3;
	}
	else if (sqr % 3 == 0) {
		col = 6;
	}
	return col;
}

/* Need a way to check scenario in which only one tile in a square
   can be a specific number and place a tile accordingly */
void Solver::checkSquare(int sqr) {
	checkSquareCalls++;

	int row = getSquareStartRow(sqr);
	int col = getSquareStartCol(sqr);
	// loop through the tiles in the square; if for all tiles, only one shows potential for a certain #, then add it to the setQueue
	int count = 0;
	int val = 1;
	while (val < 10) {
		int refr = -1;
		int refc = -1;
		for (int i = row; i < row + 3; i++) {
			for (int j = col; j < col + 3; j++) {
				if (!tiles[i][j]->hasVal()) {
					if (tiles[i][j]->hasPotential(val)) {
						count++;
						refr = i;
						refc = j;
					}
				}
            if (count > 3) {
               break;
            }
			}
         if (count > 3) {
            break;
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
				if (tiles[refr][col + i]->hasPotential(val)) {
					alignedR++;
				}
				if (tiles[row + i][refc]->hasPotential(val)) {
					alignedC++;
				}
			}
			if (alignedR == count) {
            if (rowPotential[refr][val - 1] > count) {
               updateTilePotentialInRow(refr, val, sqr);
            }
			}
			else if (alignedC == count) {
            if (colPotential[refc][val - 1] > count) {
               updateTilePotentialInCol(refc, val, sqr);
            }
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
	checkAdjSquaresCalls++;

	int row = getSquareStartRow(sqr);
	int col = getSquareStartCol(sqr);
	int rowAdj = 1;
	int colAdj = 1;
	if (row == 3) {
		rowAdj = 4;
	}
	else if (row == 6) {
		rowAdj = 7;
	}
	if (col == 3) {
		colAdj = 2;
	}
	else if (col == 6) {
		colAdj = 3;
	}
	for (int idx = 0; idx < 3; idx++) {
		if (colAdj + idx * 3 != sqr) {
			checkSquare(colAdj + idx * 3);
		}
		if (rowAdj + idx != sqr) {
			checkSquare(rowAdj + idx);
		}
	}
}

void Solver::checkRowPotential(int row) {
	checkRowPotentialCalls++;

	for (int potentialValIdx = 0; potentialValIdx < 9; potentialValIdx++) {
		if (rowPotential[row][potentialValIdx] == 1) {
			for (int colIdx = 0; colIdx < 9; colIdx++) {
				if (tiles[row][colIdx]->hasPotential(potentialValIdx + 1) && !tiles[row][colIdx]->hasBeenQueued()) {
					setQueue.push(tiles[row][colIdx]);
					tiles[row][colIdx]->setQueueState(true);
					tiles[row][colIdx]->updatePotential(potentialValIdx + 1);
				}
			}
		}
	}
}

void Solver::checkColPotential(int col) {
	checkColPotentialCalls++;

	for (int potentialValIdx = 0; potentialValIdx < 9; potentialValIdx++) {
		if (colPotential[col][potentialValIdx] == 1) {
			for (int rowIdx = 0; rowIdx < 9; rowIdx++) {
				if (tiles[rowIdx][col]->hasPotential(potentialValIdx + 1) && !tiles[rowIdx][col]->hasBeenQueued()) {
					setQueue.push(tiles[rowIdx][col]);
					tiles[rowIdx][col]->setQueueState(true);
					tiles[rowIdx][col]->updatePotential(potentialValIdx + 1);
				}
			}
		}
	}
}

void Solver::updateRowPotential(int row) {
	updateRowPotentialCalls++;

	for (int colIdx = 0; colIdx < 9; colIdx++) {
		if (rowPotential[row][colIdx] > 1) {
			rowPotential[row][colIdx]--;
		}
	}
}

void Solver::updateColPotential(int col) {
	updateColPotentialCalls++;

	for (int rowIdx = 0; rowIdx < 9; rowIdx++) {
		if (colPotential[rowIdx][col] > 1) {
			colPotential[rowIdx][col]--;
		}
	}
}

std::string Solver::getDebugInfo() {
	std::string printString;
	printString.append("Total SetTile Calls: " + std::to_string(setTileCalls) + "\n");
	printString.append("Total CheckSquare Calls: " + std::to_string(checkSquareCalls) + "\n");
	printString.append("Total CheckAdjSquares Calls: " + std::to_string(checkAdjSquaresCalls) + "\n");
	printString.append("Total CheckRowPotential Calls: " + std::to_string(checkRowPotentialCalls) + "\n");
	printString.append("Total CheckColPotential Calls: " + std::to_string(checkColPotentialCalls) + "\n");
	printString.append("Total CheckBoard Calls: " + std::to_string(checkBoardCalls) + "\n");
	printString.append("Total UpdateTilePotentialInRow Calls: " + std::to_string(updateTilePotentialInRowCalls) + "\n");
	printString.append("Total UpdateTilePotentialInCol Calls: " + std::to_string(updateTilePotentialInColCalls) + "\n");
	printString.append("Total UpdateTilePotentialInSqr Calls: " + std::to_string(updateTilePotentialInSqrCalls) + "\n");
	printString.append("Total UpdateRowPotential Calls: " + std::to_string(updateRowPotentialCalls) + "\n");
	printString.append("Total UpdateColPotential Calls: " + std::to_string(updateColPotentialCalls) + "\n");
	return printString;
}