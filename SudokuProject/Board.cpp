#include "Board.h"

Board::Board() {
	for (int i = 0; i < 9; i++) {
		boardLines.push_back("| | | | | | | | | |");
	}
}

Board::Board(Puzzle* puz) {
	puzzle = puz;
	std::vector<std::vector<Tile*>> tiles = puzzle->getTiles();
	std::string line = "|";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tiles[i][j]->getVal() != -1) {
				line.append(std::to_string(tiles[i][j]->getVal()) + "|");
			}
			else {
				line.append(" |");
			}
		}
		boardLines.emplace(boardLines.begin() + i, line);
		line = "|";
	}
}

std::string Board::getFlatLine() {
	 return flatLine;
}

std::string Board::getDivLine() {
	return divLine;
}

std::string Board::getBoxLine() {
	return boxLine;
}

std::string Board::getLine(int line) {
   return boardLines.at(line);
}

std::string Board::getBoard() {
	std::string board;
	for (int i = 0; i < 19; i++) {
		if (i == 0 || i == 18) {
			board += getFlatLine();
			board += "\n";
		}
		else if (i % 6 == 0) {
			board += getBoxLine();
			board += "\n";
		}
		else if (i % 2 == 0) {
			board += getDivLine();
			board += "\n";
		}
		else {
			board += getLine((i - 1) / 2);
			board += "\n";
		}
	}
	return board;
}

void Board::updateLines() {
	std::vector<std::string> newLines;
	std::vector<std::vector<Tile*>> tiles = puzzle->getTiles();
	std::string line = "|";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tiles[i][j]->getVal() != -1) {
				line.append(std::to_string(tiles[i][j]->getVal()) + "|");
			}
			else {
				line.append(" |");
			}
		}
		newLines.emplace(newLines.begin() + i, line);
		line = "|";
	}
	boardLines = newLines;
}