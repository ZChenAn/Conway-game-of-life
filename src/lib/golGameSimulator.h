#pragma once
#ifndef GOLGAMESIMULATOR_H
#define GOLGAMESIMULATOR_H
using namespace std;

#include "golGrid.h"

namespace gol
{
	class GameSimulator
	{
	public:
		GameSimulator(int rows, int columns);
		GameSimulator(int rows, int columns, int num_alive_cells);
		GameSimulator(string filename);
		void takeStep();
		void printGrid();
		Grid game_grid;
	};
} // end namespace
#endif