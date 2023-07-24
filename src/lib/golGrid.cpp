#include "golGrid.h"
using namespace std;

namespace gol
{
	Grid::Grid(int rows, int columns) : grid_rows(rows), grid_cols(columns)
	{
		if (rows <= 0 || columns <= 0) // check the reasonableness of the input rows and columns
		{
			throw logic_error("Expected positive integer values for rows and columns.");
		}
		initialiseGrid();
	}

	Grid::Grid(int rows, int columns, int alive_cells) : grid_rows(rows), grid_cols(columns)
	{
		if (rows <= 0 || columns <= 0 || alive_cells < 0) // check the reasonableness of the input rows,columns and alive_cells
		{
			throw logic_error("Expected positive integer values for rows and columns, and non-negative for alive cells.");
		}
		if (alive_cells > rows * columns) // check the reasonableness of the relation between the input rows,columns and alive_cells
		{
			throw logic_error("Input too many alive cells for the specified grid size.");
		}

		initialiseGrid(alive_cells);
	}

	Grid::Grid(string filename)
	{

		initialiseGrid(filename);
	}

	void Grid::printGrid() const
	{
		for (int i = 0; i < grid_rows; i++)
		{
			for (int j = 0; j < grid_cols; j++)
			{
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
	}

	char Grid::getCell(int row, int column) const
	{
		if (row < 0 || column < 0) // check the reasonableness of the input rows and columns
		{
			throw logic_error("Expected positive integer values for rows and columns.");
		}
		if (row >= grid_rows || column >= grid_cols) // check the reasonableness of the relation between input rows and columns and grid size
		{
			throw logic_error("Input row and column indices should within the grid size");
		}
		return grid[row][column];
	}

	void Grid::setCell(int row, int column, char status)
	{
		if (row < 0 || column < 0) // check the reasonableness of the input rows and columns
		{
			throw logic_error("Expected positive integer values for rows and columns.");
		}
		if (row >= grid_rows || column >= grid_cols) // check the reasonableness of the relation between input rows and columns and grid size
		{
			throw logic_error("Input row and column indices should within the grid size");
		}
		if (status == 'o' || status == '-')
		{
			grid[row][column] = status;
		}
		else
		{
			throw logic_error("Wrong input status character"); // check the reasonableness of the status character
		}
	}

	int Grid::fetching_Live_Neighbours(int row, int column) const
	{
		if (row < 0 || column < 0) // check the reasonableness of the input rows and columns
		{
			throw logic_error("Expected positive integer values for rows and columns.");
		}
		if (row >= grid_rows || column >= grid_cols) // check the reasonableness of the relation between input rows and columns and grid size
		{
			throw logic_error("Input row and column indices should within the grid size");
		}
		int count = 0;
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = column - 1; j <= column + 1; j++)
			{
				if (i < 0 || i >= grid_rows || j < 0 || j >= grid_cols) // check boundary
				{
					continue;
				}
				if (grid[i][j] == 'o')
				{
					count++;
					if (i == row && j == column) // eliminate itself
					{
						count--;
					}
				}
			}
		}
		return count;
	}

	void Grid::initialiseGrid()
	{
		rng.seed(random_device{}());
		uniform_int_distribution<int> dist_binary(0, 1); // random choose 0 or 1, 0 -> '-', 1 -> 'o'
		grid.resize(grid_rows);
		for (int i = 0; i < grid_rows; i++)
		{
			grid[i].resize(grid_cols, '-');
			for (int j = 0; j < grid_cols; j++)
			{
				int num = dist_binary(rng);
				if (num == 1)
				{
					grid[i][j] = 'o';
				}
			}
		}
	}

	void Grid::initialiseGrid(int alive_cells)
	{
		rng.seed(random_device{}());
		uniform_int_distribution<int> dist_row(0, grid_rows - 1);
		uniform_int_distribution<int> dist_column(0, grid_cols - 1);
		grid.resize(grid_rows);
		for (int i = 0; i < grid_rows; i++)
		{
			grid[i].resize(grid_cols, '-');
		}
		for (int i = 0; i < alive_cells; i++)
		{
			int row = dist_row(rng);	   // random choose row index
			int column = dist_column(rng); // random choose column index
			if (grid[row][column] == 'o')
			{
				i--;
				continue;
			}
			grid[row][column] = 'o';
		}
	}

	void Grid::initialiseGrid(string filename)
	{
		ifstream file(filename);
		if (file.is_open())
		{
			string line;
			vector<string> lines;

			while (getline(file, line))
			{
				line.erase(remove(line.begin(), line.end(), ' '), line.end()); // erase the single whitespaces
				if (line.back() == '\r' || line.back() == '\n')
				{
					line.pop_back();
				}
				lines.push_back(line);
			}

			grid_rows = lines.size();
			grid_cols = lines[0].size();
			grid.resize(grid_rows);
			for (int i = 0; i < grid_rows; i++)
			{
				grid[i].resize(grid_cols);
				for (int j = 0; j < grid_cols; j++)
				{
					grid[i][j] = lines[i][j]; // assign cells in the file to the grid
				}
			}
		}
		else
		{
			throw logic_error("Failed to open the file, please check the filepath."); // check the reasonableness of the input filename
		}

		file.close();
	}
} // end namespace