
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Andrew Bragg
//
// File        :  flipitEngine.cpp
//
//
// Description :  Definitions for the Grid class.
//


#include  "../include/flipIt.h"
#include "../include/grid.h"
#include  <assert.h>
#include  <stdlib.h>
#include  <iostream>
#include  <string.h>
#include  <limits.h>

int PATTERN_CROSS[9]	= {0, 1, 0, 1, 1, 1, 0, 1, 0};
int PATTERN_X[9] 		= {1, 0, 1, 0, 1, 0, 1, 0, 1};
int PATTERN_SQUARE[9] 	= {1, 1, 1, 1, 1, 1, 1, 1, 1};
int PATTERN_HOLLOW[9] 	= {1, 1, 1, 1, 0, 1, 1, 1, 1};
int PATTERN_CORNERS[9]	= {1, 0, 1, 0, 0, 0, 1, 0, 1};

using  namespace  std;

int* FlipIt::getPatternMatrix()
{
	int* retVal;
	switch (this->m_pattern)
	{
		case FlipIt::cross_:
			retVal = PATTERN_CROSS;
			break;

		case FlipIt::x_:
			retVal = PATTERN_X;
			break;

		case FlipIt::square_:
			retVal = PATTERN_CROSS;
			break;

		case FlipIt::hollowSquare_:
			retVal = PATTERN_CROSS;
			break;

		case FlipIt::corners_:
			retVal = PATTERN_CROSS;
			break;

	}
	return retVal;
};

//
// Constructor
//
FlipIt::FlipIt(int rows, int cols, int seed, int complexity, FlipIt::Pattern pattern, bool wrap)  : 
	m_grid(rows, cols),
	m_pattern(pattern),
	m_wrap(wrap)
{
	srand(seed);
	for (int _ = 0; _ < complexity; _++)
		this->click(rand() % (rows - 1), rand() % (cols - 1));
}

int FlipIt::numRows() const
{
	return m_grid.numRows();
}


int FlipIt::numCols() const
{
	return m_grid.numCols();
}

FlipIt::Color FlipIt::fetch(int row, int col) const
{
	return (FlipIt::Color) m_grid.fetch(row, col);
}

bool FlipIt::done() const
{
	bool retVal = true;
	int w = m_grid.numCols();
	int h = m_grid.numRows();

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++){
			retVal &= m_grid.fetch(x, y);
		}
	}
	return retVal;
}


void FlipIt::toggleSquare(int row, int col)
{
	if (!m_grid.fetch(row, col))
		m_grid.set(row, col);
	else
		m_grid.clear(row, col);
}

void FlipIt::click(int row, int col)
{
	//int* pattern = getPatternMatrix();
	toggleSquare(row, col);
}
