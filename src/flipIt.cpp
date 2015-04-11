/**********************************************************************
 * Assignment  :  #1
 * Class       :  CST 136
 * Author      :  Andrew Bragg
 * File        :  flipIt.cpp
 * Description :  FlipIt Engine.
 *********************************************************************/

#include  <iostream>
#include  <stdlib.h>
#include  <string.h>
#include  <limits.h>
#include  <assert.h>
#include  "../include/flipIt.h"
#include "../include/grid.h"

using  namespace  std;

int PATTERN_CROSS[9]    = {0, 1, 0,
						   1, 1, 1,
						   0, 1, 0};

int PATTERN_X[9]        = {1, 0, 1,
						   0, 1, 0,
						   1, 0, 1};

int PATTERN_SQUARE[9]   = {1, 1, 1,
						   1, 1, 1,
						   1, 1, 1};

int PATTERN_HOLLOW[9]   = {1, 1, 1,
						   1, 0, 1,
						   1, 1, 1};

int PATTERN_CORNERS[9]  = {1, 0, 1,
						   0, 0, 0,
						   1, 0, 1};

int DIRECTIONS[][3] = {{-1, -1}, {0, -1}, {1, -1},
					   {-1,  0}, {0,  0}, {1,  0},
					   {-1,  1}, {0,  1}, {1,  1}};

/**********************************************************************
 * Return the 3x3 binary matrix for the specified pattern
 *********************************************************************/
int* FlipIt::getDirectionList()
{
	int* retVal;
	switch (this->m_pattern)
	{
		case FlipIt::cross_:		retVal = PATTERN_CROSS;
			break;
		case FlipIt::x_:			retVal = PATTERN_X;
			break;
		case FlipIt::square_:		retVal = PATTERN_SQUARE;
			break;
		case FlipIt::hollowSquare_: retVal = PATTERN_HOLLOW;
			break;
		case FlipIt::corners_: 		retVal = PATTERN_CORNERS;
			break;
	}
	return retVal;
};

/**********************************************************************
 * Constructor
 *********************************************************************/
FlipIt::FlipIt(int rows,
			   int cols,
			   int seed,
			   int complexity,
			   FlipIt::Pattern pattern,
			   bool wrap)  :
	m_grid(rows, cols),
	m_pattern(pattern),
	m_wrap(wrap)
{
	srand(seed);
	for (int _ = 0; _ < complexity; _++)
		this->click(rand() % (rows - 1), rand() % (cols - 1));
}


/**********************************************************************
 * Check to see if all cells are off
 *********************************************************************/
bool FlipIt::done() const
{
	bool retVal = true;
	int w = m_grid.numCols();
	int h = m_grid.numRows();

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			retVal &= !((bool)m_grid.fetch(y, x));

	return retVal;
}

/**********************************************************************
 * Toggles the on/off state of a cell
 *********************************************************************/
void FlipIt::toggleCell(int row, int col)
{
	assert( row >= 0  &&  row < m_grid.numRows() );
	assert( col >= 0  &&  col < m_grid.numCols() );

	if (!m_grid.fetch(row, col))
		m_grid.set(row, col);
	else
		m_grid.clear(row, col);
}

int FlipIt::getWrappedNeighbor(int i, int dx, int dy) const
{
	int w = numCols();
	int x = getWrapped_x(i, dx);
	int y = getWrapped_y(i, dy);
	return x + (y * w);
}
int FlipIt::getWrapped_x(int i, int dx) const
{
	int w = numCols();
	int h = numRows();

	int x = i % w;

	// Check to make sure 0 < i < grid_size
	if (i >= w * h or i < 0)
		return -1;


	if (x + dx >= w)
		x -= (w - 1);
	else if (x + dx < 0)
		x += (w - 1);
	else
		x += dx;

	return x;
}
int FlipIt::getWrapped_y(int i, int dy) const
{
	int w = numCols();
	int h = numRows();

	int y = i / w;

	// Check to make sure 0 < i < grid_size
	if (i >= w * h or i < 0)
		return -1;


	if (y + dy >= h)
		y -= (h - 1);
	else if (y + dy < 0)
		y += (h - 1);
	else
		y += dy;

	return y;
}

/**********************************************************************
 * Apply a toggle of all cells in the pattern at the specified center
 *********************************************************************/
void FlipIt::click(int row, int col)
{
	int* p_pattern = getDirectionList();
	int w = m_grid.numCols();
	int dx, dy;
	int _x = 0;
	int _y = 1;

	for (int i = 0; i < 9; i++)
	{
		if (p_pattern[i])
		{
			int home = col + (row * w);
			dx = DIRECTIONS [i][_x];
			dy = DIRECTIONS [i][_y];
			//int new_i = getWrappedNeighbor(home, dx, dy);
			int new_x = getWrapped_x(home, dx);
			int new_y = getWrapped_y(home, dy);
			//toggleCell(new_i / w, new_i % w);
			toggleCell(new_y, new_x);
		}
	}
}
