/**********************************************************************
 * Assignment  :  #1
 * Class       :  CST 136
 * Author      :  Andrew Bragg
 * File        :  flipIt.cpp
 * Description :  FlipIt Engine.
 *********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "../include/flipIt.h"
#include "../include/grid.h"

using  namespace  std;

const int PAT_SIZE = 9;

int PAT_DEFAULT[PAT_SIZE]  	= {0, 0, 0, 0, 1, 0, 0, 0, 0};
int PAT_CROSS[PAT_SIZE]    	= {0, 1, 0, 1, 1, 1, 0, 1, 0};
int PAT_X[PAT_SIZE]        	= {1, 0, 1, 0, 1, 0, 1, 0, 1};
int PAT_SQUARE[PAT_SIZE]   	= {1, 1, 1, 1, 1, 1, 1, 1, 1};
int PAT_HOLLOW[PAT_SIZE]   	= {1, 1, 1, 1, 0, 1, 1, 1, 1};
int PAT_CORNERS[PAT_SIZE]  	= {1, 0, 1, 0, 0, 0, 1, 0, 1};

int DIRS[][3] 				= {{-1, -1}, {0, -1}, {1, -1},
							   {-1,  0}, {0,  0}, {1,  0},
							   {-1,  1}, {0,  1}, {1,  1}};

/**********************************************************************
 * Constructor. Initializes board by clicking it in complexity random
 * cells. Also initiializes grid, pattern, and wrap members.
 *********************************************************************/
FlipIt::FlipIt(int rows, int cols,
			   int seed, int complexity,
			   FlipIt::Pattern pattern, bool wrap)  :
	m_grid(rows, cols),
	m_pattern(pattern),
	m_wrap(wrap)
{
	srand(seed);
	for (int n = 0; n < complexity; n++)
		this->click(rand() % (rows - 1), rand() % (cols - 1));
}

/**********************************************************************
 * Check to see if all cells are off
 *********************************************************************/
bool FlipIt::done() const
{
	bool retVal = true;
	for (int x = 0; x < numCols(); x++)
		for (int y = 0; y < numRows(); y++)
			retVal &= !((bool)m_grid.fetch(y, x));
	return retVal;
}

/**********************************************************************
 * Toggles the on/off state of a cell
 *********************************************************************/
void FlipIt::toggleCell(int row, int col)
{
	if (!m_grid.fetch(row, col)) 	m_grid.set(row, col);
	else 							m_grid.clear(row, col);
}

/**********************************************************************
 * Returns wrapped index
 * 	d - delta - the change in p
 * 	p - the value being wrapped
 * 	v - size of the wrap cycle
 *********************************************************************/
int FlipIt::_neighbor(int p, int d, int v) const
{
	if (!m_wrap && (p + d >= v || p + d < 0)) return -1;
	if (p + d >= v) 		p -= v;
	else if (p + d < 0) 	p += v;
	return p + d;
}

/**********************************************************************
 * Accepts an index to be converted to a x value. Returns the x value
 * of the neighbor index in direction dx
 *********************************************************************/
int FlipIt::neighbor_x(int i, int dx) const
{
	return _neighbor(i % numCols(), dx, numCols());
}

/**********************************************************************
 * Accepts an index to be converted to a y value. Returns the y value
 * of the neighbor index in direction dy
 *********************************************************************/
int FlipIt::neighbor_y(int i, int dy) const
{
	return _neighbor(i / numCols(), dy, numRows());
}

/**********************************************************************
 * Apply a toggle of all cells in the pattern at the specified center
 *********************************************************************/
void FlipIt::click(int row, int col)
{
	int *p_pattern = getPattern();
	int home = col + (row *  numCols());

	for (int i = 0; i < PAT_SIZE; i++)
	{
		if (p_pattern[i])
		{
			int x = neighbor_x(home, DIRS[i][0]);
			int y = neighbor_y(home, DIRS[i][1]);
			if (x > -1 and y > -1) toggleCell(y, x);
		}
	}
}

/**********************************************************************
 * Return the 3x3 binary matrix for the specified pattern
 *********************************************************************/
int* FlipIt::getPattern() const
{
	switch (this->m_pattern)
	{
		case FlipIt::cross_:		return PAT_CROSS;
		case FlipIt::x_:			return PAT_X;
		case FlipIt::square_:		return PAT_SQUARE;
		case FlipIt::hollowSquare_: return PAT_HOLLOW;
		case FlipIt::corners_: 		return PAT_CORNERS;
		default: 					return PAT_DEFAULT;
	}
};