#pragma once
#ifndef GOLGRID_H
#define GOLGRID_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

namespace gol
{
	// create the class to store the status (alive or dead) of the 2D grid of cells
	class Grid
	{
	public:
		Grid(int rows, int columns);
		Grid(int rows, int columns, int alive_cells);
		Grid(string filename);

		void printGrid() const;
		char getCell(int row, int column) const;
		void setCell(int row, int column, char status);
		// calculating the number of neighbouring cells for a cell
		int fetching_Live_Neighbours(int row, int column) const;

		int grid_rows;
		int grid_cols;
		vector<vector<char>> grid;
		mt19937 rng;

	private:
		void initialiseGrid();				  // initialise grid randomly
		void initialiseGrid(int alive_cells); // initialise grid with number of alive cells
		void initialiseGrid(string filename); // initialise grid with input file
	};
} // end namespace

#endif