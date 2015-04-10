
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


#include  "../include/flipitEngine.h"
#include "../include/grid.h"
#include  <assert.h>
#include  <stdlib.h>
#include  <iostream>
#include  <string.h>
#include  <limits.h>

using  namespace  std;


//
// Constructor
//
FlipIt::FlipIt(int rows, int cols, int seed, int complexity, FlipIt::Pattern pattern, bool wrap)  : 
	m_grid(rows, cols),
	m_color(FlipIt::Color (false))
{
	cout << "FlipIt constructor";
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
	return this->m_color;
}

bool FlipIt::done() const
{
	return false;
}

void FlipIt::click(int row, int col)
{
	cout << "click";
}
