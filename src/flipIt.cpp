/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #1
 * File        :  flipIt.cpp
 * Description :  FlipIt Engine.
 *********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "flipIt.h"
#include "sgrid.h"

using  namespace  std;

const int PAT_SIZE = 9;



const int DIRS[][3] 				= {{-1, -1}, {0, -1}, {1, -1},
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

	//click the board in a random location 'complexity' times
	for (int n = 0; n < complexity; n++)
		this->click(rand() % (rows), rand() % (cols));
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
int FlipIt::_neighbor(int val, int delta, int size) const
{
	// If wrapping isn't allowed and the value would wrap, return -1
	if (!m_wrap && (val + delta >= size || val + delta < 0))
		return -1;

	// If we are stepping off the edge, wrap around
	if (val + delta >= size) 		val -= size;
	else if (val + delta < 0) 		val += size;

	// return value some delta representing the neighbor direction
	return val + delta;
}

/**********************************************************************
 * Accepts an index to be converted to a x value. Returns the x value
 * of the neighbor index in direction dx
 *********************************************************************/
int FlipIt::neighbor_x(int i, int dx) const
{
	// Based on a 1D array index, calculate the x val
	// and find its neighbor
	return _neighbor(i % numCols(), dx, numCols());
}

/**********************************************************************
 * Accepts an index to be converted to a y value. Returns the y value
 * of the neighbor index in direction dy
 *********************************************************************/
int FlipIt::neighbor_y(int i, int dy) const
{
	// Based on a 1D array index, calculate the y val
	// and find its neighbor
	return _neighbor(i / numCols(), dy, numRows());
}

/**********************************************************************
 * Apply a toggle of all cells in the pattern at the specified center
 *********************************************************************/
void FlipIt::click(int row, int col)
{
	// List of nine ones and zeros that represent a pattern
	int *p_pattern = getPattern();
	int home = col + (row *  numCols());

	for (int i = 0; i < PAT_SIZE; i++)
	{
		if (p_pattern[i])
		{
			int x = neighbor_x(home, DIRS[i][0]);
			int y = neighbor_y(home, DIRS[i][1]);
			// If the neigbor index is valid, toggle the cell
			if (x > -1 and y > -1) toggleCell(y, x);
		}
	}
}

int PAT_DEFAULT[PAT_SIZE]  	= {0, 0, 0, 0, 1, 0, 0, 0, 0};
int PAT_CROSS[PAT_SIZE]    	= {0, 1, 0, 1, 1, 1, 0, 1, 0};
int PAT_X[PAT_SIZE]        	= {1, 0, 1, 0, 1, 0, 1, 0, 1};
int PAT_SQUARE[PAT_SIZE]   	= {1, 1, 1, 1, 1, 1, 1, 1, 1};
int PAT_HOLLOW[PAT_SIZE]   	= {1, 1, 1, 1, 0, 1, 1, 1, 1};
int PAT_CORNERS[PAT_SIZE]  	= {1, 0, 1, 0, 0, 0, 1, 0, 1};

/**********************************************************************
 * Return the binary list of nine for the specified pattern
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