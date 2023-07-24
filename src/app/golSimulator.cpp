#include "golGrid.h"
#include "golGameSimulator.h"
#include <cstdlib>
#include <getopt.h>
using namespace gol;

// help message for command line
void print_help_message()
{
    cout << "Usage: gofSimulator [OPTIONS]\n"
         << "Options:\n"
         << "-f <filename>\t\t\t\t specifying a text file input\n"
         << "-r <rows> <columns> <alive_cells>\t specifying random alive cells initial\n"
         << "-i <iterations>\t\t\t\t the number of iterations to simulate\n"
         << "-h \t\t\t\t\t print related help message\n"
         << "sample command input:\n"
         << "-r 7 7 15 -i 4\n"
         << "-f ../test/data/glider.txt -i 4\n";
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_help_message();
        return 0;
    }

    string filename;
    // assign initial value for future option providing check
    int rows = -1, columns = -1, alive_cells = -1, iterations = -1;

    int opt;
    while ((opt = getopt(argc, argv, "f:r:g:i:h")) != -1)
    {
        switch (opt)
        {
        case 'f':
            filename = optarg;
            break;
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
        case 'h':
            print_help_message();
            return 0;
        default:
            cerr << "Error: Invalid option -" << static_cast<char>(optopt) << "" << endl;
            print_help_message();

            return 1;
        }
    }

    if (filename.empty() && (rows == -1 || columns == -1 || alive_cells == -1))
    {
        cerr << "Error: Either option -f or option -r must be provided." << endl;
        print_help_message();

        return 1;
    }

    if (!filename.empty() && (rows != -1 || columns != -1 || alive_cells != -1))
    {
        cerr << "Error: Options -f and -r cannot be used together." << endl;
        print_help_message();
        return 1;
    }

    if (iterations == -1)
    {
        cerr << "Error: option -i must be provided." << endl;
        print_help_message();

        return 1;
    }

    if (!filename.empty())
    {
        GameSimulator game(filename);
        for (int i = 0; i < iterations; i++)
        {
            if (i == 0)
            {
                cout << "Origin grid" << endl;
                game.printGrid();
            }
            game.takeStep();
            cout << "Iteration: " << i + 1 << endl;
            game.printGrid();
        }
    }
    else
    {
        GameSimulator game(rows, columns, alive_cells);
        for (int i = 0; i < iterations; i++)
        {
            if (i == 0)
            {
                cout << "Origin grid" << endl;
                game.printGrid();
            }
            game.takeStep();
            cout << "Iteration: " << i + 1 << endl;
            game.printGrid();
        }
    }
}