# Conway-game-of-life

Purpose
-------

This project is the PHAS0100 2022/23 Assignment 1 Game of Life Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Credits
-------

The main code of the project is written by myself, please not directly copy it.

This project is maintained by [Dr. Jamie Quinn](http://jamiejquinn.com/). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](https://github-pages.ucl.ac.uk/research-computing-with-cpp/) course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james) and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).

Build Instructions
------------------

To run cmake:

```
cmake -B build
```

To compile:

```
cmake --build build
```

I have added the files golGridTest.cpp and golGameSimulatorTest.cpp in test folder which are included the required tests in the coursework1 requirements.  

To test:

```
cd build
ctest
```

I have added the files golSimulator.cpp and golStationaryPattern.cpp which are two required command line application in the coursework1 requirements. 


To run game simulator command line:

File initialise:

```
cd build
./bin/golSimulator -f <filename> -i <iterations>
```

Sample input:

```
./bin/golSimulator -f ../test/data/glider.txt -i 4
```

Random initialise:

```
cd build
./bin/golSimulator -r <rows> <columns> <alive_cells> -i <iterations>
```

Sample input:

```
./bin/golSimulator -r 7 7 15 -i 4
```

To run finding stationary patterns command line:

If you do not input -c \<calls>. The default number of different random initial conditions calls is 500.

```
cd build
./bin/golStationaryPattern -r <rows> <columns> <alive_cells> -i <iterations> -c <calls>
```

Sample input:

```
./bin/golStationaryPattern -r 4 4 4 -i 10
./bin/golStationaryPattern -r 4 4 4 -i 10 -c 1000
```

Number of still lifes found
------------------

The following table shows the stationary pattern I found for different active cells in the 4*4 grid. For the command parameters to generate this table, the number of iterations is 10 and the number of different random initial conditions calls is 500. The same stationary pattern located in different locations of the grid will also be counted, please see the image 3.d_3_alive_cells_still_lifes.png for details. For some of the active cells, I found too many stationary patterns, so my screenshots will only put the cases for 3, 4, and 5 alive cells. If you want to see the rest, please run my code. 

For a 4*4 grid, there are $2^{16}$ = 65536 initialization cases, but our default calls are only set to 500, so for cases like active_cells equal to 6, 7... , the number of stationary patterns found in each run may be different.

| Alive Cells Number | Stationary Pattern Number |
| :----------------: | :-----------------------: |
|         1          |             0             |
|         2          |             0             |
|         3          |             9             |
|         4          |            18             |
|         5          |            41             |
|         6          |            50             |
|         7          |            57             |
|         8          |            62             |
|         9          |            68             |
|         10         |            63             |
|         11         |            50             |
|         12         |            25             |
|         13         |            14             |
|         14         |             4             |
|         15         |             0             |

