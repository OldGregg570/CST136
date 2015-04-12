FlipIt
======

---
The game board consists a grid (rows and columns) of cells. Each cell can be
one of two colors: solid or clear. The user will select a cell. This action will
result in a pattern of nearby cells to switch colors. The goal is to select
cells in the correct order so that the grid becomes totally clear.

The game has the following user-selectable settings:

- Number of rows: the number of rows of cells in the grid.
- Number of columns: the number of columns of cells in the grid.
- Game number: determines the starting point for setting up the game.
- Complexity: determines the difficulty level for the game.
- Pattern: determines which nearby grid positions have their color switched
  when a cell is selected.
- Wrap flag: an indication of whether patterns are cut-off by the grid
  borders or "wrapped" to the other side of the grid.

Requirements
------------

- GNU make or mingw32-make

Build instructions
------------------

######To build:
    make

######To build and run the test suite:
    make test

######Start the game:
    make start

Optional Commands
----------------

######To run GCOV code coverage:
    make cover