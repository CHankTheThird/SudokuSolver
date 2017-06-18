#include "Board.h"

Board::Board() {
	flatLine = "-------------------";
	divLine = "|-----|-----|-----|";
	boxLine = "|=====+=====+=====|";
	for (int i = 0; i < 9; i++) {
		lines.push_back("| | | | | | | | | |");
	}
}

Board::Board(Puzzle* p) {
	puz = p;
	flatLine = "-------------------";
	divLine = "|-----|-----|-----|";
	boxLine = "|=====+=====+=====|";
	std::vector<std::vector<Tile*>> tiles = p->getTiles();
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
		lines.emplace(lines.begin() + i, line);
		line = "|";
		//lines.push_back("|X|X|X|X|X|X|X|X|X|");
	}
}

std::string Board::getLine(int line) {
	return lines.at(line);
}

std::string Board::printFlatLine() {
	 return flatLine;
}

std::string Board::printDivLine() {
	return divLine;
}

std::string Board::printBoxLine() {
	return boxLine;
}

std::string Board::printBoard() {
	std::string board;
	for (int i = 0; i < 19; i++) {
		if (i == 0 || i == 18) {
			board += printFlatLine();
			board += "\n";
		}
		else if (i % 6 == 0) {
			board += printBoxLine();
			board += "\n";
		}
		else if (i % 2 == 0) {
			board += printDivLine();
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
	std::vector<std::vector<Tile*>> tiles = puz->getTiles();
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
		//lines.push_back("|X|X|X|X|X|X|X|X|X|");
	}
	lines = newLines;
}