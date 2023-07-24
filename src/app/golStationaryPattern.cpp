#include "golGrid.h"
#include "golGameSimulator.h"
#include <cstdlib>
#include <getopt.h>
using namespace gol;

// check if two grids is the same except all dead cells grid, using for find still pattern  
bool isGridsEqual(Grid grid1, Grid grid2, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid1.getCell(i, j) != grid2.getCell(i, j))
            {
                return false;
            }
        }
    }
    bool is_all_dashes = true;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid1.getCell(i, j) == 'o')
            {
                is_all_dashes = false;
            }
        }
    }
    if (is_all_dashes)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// help message for command line
void print_help_message()
{
    cout << "Usage: gofSimulator [OPTIONS]\n"
         << "Options:\n"
         << "-r <rows> <columns> <alive_cells>\t specifying random alive cells initial\n"
         << "-i <iterations>\t\t\t\t the number of iterations to simulate\n"
         << "-c <calls>\t\t\t\t specifying number of different random initial conditions calls \n"
         << "-h \t\t\t\t\t print related help message\n"
         << "sample command input:\n"
         << "-r 4 4 4 -i 10\n"
         << "-r 4 4 4 -i 10 -c 1000\n";
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_help_message();
        return 0;
    }

    // assign initial value for future option providing check
    int rows = -1, columns = -1, alive_cells = -1, iterations = -1, calls = 500;

    int opt;
    while ((opt = getopt(argc, argv, "r:i:c:h")) != -1)
    {
        switch (opt)
        {
        case 'r':
            if (optind + 1 >= argc)
            {
                cerr << "Error: Invalid argument for option -r\n"
                     << "Expected 3 integer values, received " << argc - optind + 1 << endl;
                return 1;
            }

            rows = atoi(argv[optind - 1]);
            columns = atoi(argv[optind]);
            alive_cells = atoi(argv[optind + 1]);

            if (rows <= 0 || columns <= 0 || alive_cells < 0)
            {
                cerr << "Error: Invalid argument values for option -r\n"
                     << "Expected positive integer values for rows and columns, and non-negative for alive cells" << endl;
                return 1;
            }
            if (alive_cells > rows * columns)
            {
                cerr << "Error: Input too many alive cells for the specified grid size" << endl;
                return 1;
            }
            
            break;
        case 'i':
            iterations = atoi(optarg);
            if (iterations <= 0)
            {
                cerr << "Error: Invalid argument value for option -i\n"
                     << "Expected a positive integer value for iterations" << endl;
                return 1;
            }
            break;
        case 'c':
            calls = atoi(optarg);
            if (calls <= 0)
            {
                cerr << "Error: Invalid argument value for option -c\n"
                     << "Expected a positive integer value for number of different random initial conditions calls" << endl;
                return 1;
            }
            break;
        case 'h':
            print_help_message();
            return 0;
        default:
            cerr << "Error: Invalid option -" << static_cast<char>(optopt) << "" << endl;
            print_help_message();

            return 1;
        }
    }

    if (rows == -1 || columns == -1 || alive_cells == -1)
    {
        cerr << "Error: option -r must be provided." << endl;
        print_help_message();

        return 1;
    }

    if (iterations == -1)
    {
        cerr << "Error: option -i must be provided." << endl;
        print_help_message();

        return 1;
    }
    cout << "Finding still life patterns...:\n";
    int count = 0;
    vector<Grid> grids;
    for (int i = 0; i < calls; i++)
    {
        GameSimulator game(rows, columns, alive_cells);
        for (int j = 0; j < iterations; j++)
        {
            Grid grid1 = game.game_grid;
            game.takeStep();
            Grid grid2 = game.game_grid;
            if (isGridsEqual(grid1, grid2, rows, columns))
            {
                if (count == 0)
                {
                    cout << "Found still life patterns:\n";
                }
                bool found_before = false;
                for (auto grid : grids)
                {
                    if (isGridsEqual(grid, game.game_grid, rows, columns))
                    {
                        found_before = true;
                        break;
                    }
                }
                if (!found_before)
                {
                    grids.push_back(game.game_grid);
                    game.printGrid();
                    count++;
                    break;
                }
            }
        }
    }
    if (count == 0)
    {
        cout << "No still life pattern found.\n";
    }
    else
    {
        cout << "Number of found still life patterns: " << count << "\n";
    }
}