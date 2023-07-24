#include "catch.hpp"
#include "golGrid.h"
#include "golGameSimulator.h"
using namespace gol;

TEST_CASE("takeStep method")
{
    SECTION("Test for grid with no live cells")
    {
        GameSimulator game(5, 5, 0);
        game.takeStep();
        int alive_cells = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (game.game_grid.getCell(i, j) == 'o')
                {
                    alive_cells = alive_cells + 1;
                }
            }
        }
        REQUIRE(alive_cells == 0);
    }

    SECTION("Test for grid with three simple cells in L shape")
    {
        GameSimulator game(3, 3, 0);
        game.game_grid.setCell(0, 0, 'o');
        game.game_grid.setCell(0, 1, 'o');
        game.game_grid.setCell(0, 2, 'o');
        game.takeStep();
        REQUIRE(game.game_grid.getCell(0, 1) == 'o');
        REQUIRE(game.game_grid.getCell(1, 1) == 'o');
    }

    SECTION("Test for grid with more live cells")
    {
        GameSimulator game(6, 6, 0);
        game.game_grid.setCell(1, 1, 'o');
        game.game_grid.setCell(1, 2, 'o');
        game.game_grid.setCell(2, 1, 'o');
        game.game_grid.setCell(4, 4, 'o');
        game.game_grid.setCell(4, 5, 'o');
        game.game_grid.setCell(5, 4, 'o');
        game.takeStep();
        REQUIRE(game.game_grid.getCell(1, 1) == 'o');
        REQUIRE(game.game_grid.getCell(1, 2) == 'o');
        REQUIRE(game.game_grid.getCell(2, 1) == 'o');
        REQUIRE(game.game_grid.getCell(2, 2) == 'o');
        REQUIRE(game.game_grid.getCell(4, 4) == 'o');
        REQUIRE(game.game_grid.getCell(4, 5) == 'o');
        REQUIRE(game.game_grid.getCell(5, 4) == 'o');
        REQUIRE(game.game_grid.getCell(5, 5) == 'o');
    }

    SECTION("Test for running two times that grid with more live cells")
    {
        GameSimulator game(6, 6, 0);
        game.game_grid.setCell(1, 1, 'o');
        game.game_grid.setCell(1, 2, 'o');
        game.game_grid.setCell(2, 1, 'o');
        game.game_grid.setCell(4, 4, 'o');
        game.game_grid.setCell(4, 5, 'o');
        game.game_grid.setCell(5, 4, 'o');
        game.takeStep();
        game.takeStep();
        REQUIRE(game.game_grid.getCell(1, 1) == 'o');
        REQUIRE(game.game_grid.getCell(1, 2) == 'o');
        REQUIRE(game.game_grid.getCell(2, 1) == 'o');
        REQUIRE(game.game_grid.getCell(2, 2) == 'o');
        REQUIRE(game.game_grid.getCell(4, 4) == 'o');
        REQUIRE(game.game_grid.getCell(4, 5) == 'o');
        REQUIRE(game.game_grid.getCell(5, 4) == 'o');
        REQUIRE(game.game_grid.getCell(5, 5) == 'o');
    }
}