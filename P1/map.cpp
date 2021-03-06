#include "map.h"
#include <iostream>
#include <ctime>

using namespace std;

Map::Map(const int& difficulty) {
	// Dimension in range [5*x, 5*x*2)
	// TODO Clarify the requeriments with the teacher
	// a medium level (2) could generate a larger
	// map than the difficult level (3)
	srand(time(NULL));
	rows = cols = (rand() % difficulty * 5 + 1) + difficulty * 5;
	map_data = static_cast<char**>(malloc(rows*sizeof(char*)));
	for (int i = 0; i < rows; ++i) {
		map_data[i] = static_cast<char*>(malloc(cols*sizeof(char)));
	}
	resetMap();
}

void Map::setCell(const int & x, const int& y, const char& content) {
	map_data[x][y] = content;
}

void Map::resetMap() {
	for (int i = 0; i < rows; ++i) {
		memset(map_data[i], '.', cols * sizeof(char));
	}
}

int Map::getRows() const {
	return rows;
}

int Map::getCols() const {
	return cols;
}

char Map::getCell(const int &x, const int & y) const {
	return map_data[x][y];
}

ostream& operator<<(ostream& os, const Map &map) {
	for (int r = 0; r < map.getRows(); ++r) {
		for (int c = 0; c < map.getCols(); ++c) {
			os << map.getCell(r, c) << " ";
		}
		os << endl;
	}
	return os;
}