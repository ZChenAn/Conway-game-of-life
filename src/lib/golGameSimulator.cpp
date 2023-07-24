#include "golGameSimulator.h"
using namespace std;

namespace gol
{
	GameSimulator::GameSimulator(int rows, int columns) : game_grid(rows, columns) {}

	GameSimulator::GameSimulator(int rows, int columns, int num_alive_cells) : game_grid(rows, columns, num_alive_cells) {}

	GameSimulator::GameSimulator(string filename) : game_grid(filename) {}

	void GameSimulator::takeStep()
	{
		vector<vector<char>> new_grid = game_grid.grid;
		for (int i = 0; i < game_grid.grid_rows; i++)
		{
			for (int j = 0; j < game_grid.grid_cols; j++)
			{
				int num_neighbours = game_grid.fetching_Live_Neighbours(i, j); //get neighbours number
				if (game_grid.getCell(i, j) == 'o')
				{
					if (num_neighbours < 2 || num_neighbours > 3) //cells to be dead
					{
						new_grid[i][j] = '-';
					}
				}
				else
				{
					if (num_neighbours == 3)
					{
						new_grid[i][j] = 'o'; //cells to be alive
					}
				}
			}
		}
		game_grid.grid = new_grid;
	}

	void GameSimulator::printGrid()
	{
		game_grid.printGrid();
		cout << endl;
		cout << string(60, '#') << endl;
		cout << endl;
	}
} // end namespace