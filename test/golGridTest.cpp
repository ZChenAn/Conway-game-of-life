#include "catch.hpp"
#include "golGrid.h"
using namespace gol;

TEST_CASE("Grid first constructor instantiation", "[Default]")
{
    SECTION("Test for exception")
    {
        REQUIRE_NOTHROW(Grid(2, 5));
        REQUIRE_NOTHROW(Grid(4, 4));
        REQUIRE_THROWS(Grid(0, 5));
        REQUIRE_THROWS(Grid(4, 0));
    }

    SECTION("Test for variable assign")
    {
        const int expected_rows = 5;
        const int expected_cols = 10;
        Grid grid(expected_rows, expected_cols);

        REQUIRE(grid.grid_rows == expected_rows);
        REQUIRE(grid.grid_cols == expected_cols);
    }

    SECTION("Test for randomly initialise correct with char o and -")
    {
        Grid grid(5, 5);

        bool is_all_dashes = true;
        bool is_all_o = true;
        bool is_all_dashes_or_o = true;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                char cell = grid.getCell(i, j);
                if (cell == 'o')
                {
                    is_all_dashes = false;
                }
                else if (cell == '-')
                {
                    is_all_o = false;
                }
                else
                {
                    is_all_dashes = false;
                    is_all_o = false;
                    is_all_dashes_or_o = false;
                }
            }
        }

        REQUIRE_FALSE(is_all_dashes);
        REQUIRE_FALSE(is_all_o);
        REQUIRE(is_all_dashes_or_o);
    }
}

TEST_CASE("Grid second constructor instantiation", "[Alive Cells]")
{

    SECTION("Test for exception")
    {
        REQUIRE_NOTHROW(Grid(2, 5, 3));
        REQUIRE_NOTHROW(Grid(4, 4, 4));
        REQUIRE_THROWS(Grid(0, 5, 2));
        REQUIRE_THROWS(Grid(4, 0, 3));
        REQUIRE_THROWS(Grid(5, 5, 30));
        REQUIRE_THROWS(Grid(4, 3, 15));
    }

    SECTION("Test for variable assign")
    {
        const int expected_rows = 5;
        const int expected_cols = 10;
        const int alive_cells = 10;
        Grid grid(expected_rows, expected_cols, alive_cells);

        REQUIRE(grid.grid_rows == expected_rows);
        REQUIRE(grid.grid_cols == expected_cols);
    }

    SECTION("Test for correct number of alive cells")
    {
        Grid grid(5, 5, 10);
        int alive_cells = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (grid.getCell(i, j) == 'o')
                {
                    alive_cells = alive_cells + 1;
                }
            }
        }
        REQUIRE(alive_cells == 10);
    }

    SECTION("Test for different instances generate different patterns of alive cells")
    {
        // Create two grids with the same rows, cols and number of alive cells
        Grid grid1(5, 10, 20);
        Grid grid2(5, 10, 20);

        // Check that the two grids generate different patterns
        bool is_pattern_different = false;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (grid1.getCell(i, j) != grid2.getCell(i, j))
                {
                    is_pattern_different = true;
                    break;
                }
            }
            if (is_pattern_different)
            {
                break;
            }
        }
        REQUIRE(is_pattern_different);
    }
}

TEST_CASE("Grid third constructor instantiation", "[File Input]")
{
    SECTION("Test for exception")
    {
        string filename = "../../test/data/glider.txt";
        string wrong_filename = "../../test/data/spider.txt";
        REQUIRE_NOTHROW(Grid(filename));
        REQUIRE_THROWS(Grid(wrong_filename));
    }

    SECTION("Test for variable assign")
    {
        string filename = "../../test/data/oscillators.txt";
        Grid grid(filename);
        REQUIRE(grid.grid_rows == 12);
        REQUIRE(grid.grid_cols == 12);
    }

    SECTION("Test for assign correct character")
    {
        string filename = "../../test/data/glider.txt";
        Grid grid(filename);
        REQUIRE(grid.getCell(1, 2) == 'o');
        REQUIRE(grid.getCell(2, 0) == 'o');
        REQUIRE(grid.getCell(2, 2) == 'o');
        REQUIRE(grid.getCell(3, 1) == 'o');
        REQUIRE(grid.getCell(3, 2) == 'o');
    }
}

TEST_CASE("Get and Set Cell method")
{
    SECTION("Test for exception")
    {
        Grid grid(5, 5);
        REQUIRE_NOTHROW(grid.setCell(2, 2, 'o'));
        REQUIRE_NOTHROW(grid.setCell(3, 3, '-'));
        REQUIRE_THROWS(grid.setCell(3, 6, 'o'));
        REQUIRE_THROWS(grid.setCell(6, 3, 'o'));
        REQUIRE_THROWS(grid.setCell(-1, 3, '-'));
        REQUIRE_THROWS(grid.setCell(3, -1, '-'));
        REQUIRE_THROWS(grid.setCell(3, 3, '+'));
    }

    SECTION("Test for character assign in the grid")
    {
        Grid grid(5, 5, 0);
        grid.setCell(2, 2, 'o');
        REQUIRE(grid.getCell(2, 2) == 'o');
    }
}

TEST_CASE("Fetching Live Neighbours method")
{
    SECTION("Test for exception")
    {
        Grid grid(5, 5, 0);
        REQUIRE_NOTHROW(grid.fetching_Live_Neighbours(2, 2));
        REQUIRE_THROWS(grid.fetching_Live_Neighbours(-1, 2));
        REQUIRE_THROWS(grid.fetching_Live_Neighbours(2, -1));
        REQUIRE_THROWS(grid.fetching_Live_Neighbours(5, 2));
        REQUIRE_THROWS(grid.fetching_Live_Neighbours(2, 5));
    }

    SECTION("Test for method effect")
    {
        Grid grid(5, 5, 0);
        grid.setCell(2, 2, 'o');
        grid.setCell(1, 1, 'o');
        grid.setCell(3, 1, 'o');
        grid.setCell(3, 2, 'o');
        grid.setCell(3, 3, 'o');
        REQUIRE(grid.fetching_Live_Neighbours(2, 2) == 4);
        REQUIRE(grid.fetching_Live_Neighbours(1, 2) == 2);
    }
}