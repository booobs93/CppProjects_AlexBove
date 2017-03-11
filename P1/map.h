#pragma once

class Map {

public:
	Map(const int& difficulty);											// Constructor

	void setCell(const int & x, const int& y, const char& content);		// Set the content for a cell
	void resetMap();													// Reset the maps emptying all the cells
	int getRows() const;												// Get the map row amount
	int getCols() const;												// Get the map's columns amount
	char getCell(const int &x, const int & y) const;					// Get the content of the cell located on (x,y) coordinates

private:
	int rows;															// The number of rows of the map
	int cols;															// The number of columns of the map
	char** map_data;													// The map data
};