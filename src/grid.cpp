
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Michael Hoffman (Instructor)
//
// File        :  grid.cpp
//
//
// Description :  Definitions for the Grid class.
//


#include  "../include/grid.h"
#include <assert.h>
#include  <stdlib.h>


//
// Constructor
//
Grid::Grid( int  nRows, int  nCols )  :
  m_numRows(nRows),
  m_numCols(nCols),
  m_cells( new  bool[ m_numRows * m_numCols] )
{
  if  (! m_cells)
    exit(EXIT_FAILURE);


  //
  // Initialize all the cells
  //
  for( int  row = 0;  row < m_numRows;  ++row )
    for( int  col = 0;  col < m_numCols;  ++col )
      clear(row, col);
}


//
// Sets the state of the cell specified by row/col
// to set.
//
void  Grid::set( int  row, int  col )
{
  assert( row >= 0  &&  row < m_numRows );
  assert( col >= 0  &&  col < m_numCols );

  m_cells[ index(row, col) ]  =  true;
}


//
// Sets the state of the cell specified by row/col
// to clear.
//
void  Grid::clear( int  row, int  col )
{
  assert( row >= 0  &&  row < m_numRows );
  assert( col >= 0  &&  col < m_numCols );

  m_cells[ index(row, col) ]  =  false;
}


//
// Returns true if the cell specified by row/col
// is set. Otherwise returns false.
//
bool  Grid::fetch( int  row, int  col )  const
{
  assert( row >= 0  &&  row < m_numRows );
  assert( col >= 0  &&  col < m_numCols );

  return  m_cells[ index(row, col) ];
}

//
// Returns the wrapped neighbor index based on a relative x value and
// a relative y value in -1, 0, or 1
//
int Grid::getWrappedNeighborIndex(int i, int rel_x, int rel_y) const
{
  int w = numCols();
  int h = numRows();

  int x = i % w;
  int y = i / w;
  int retVal;

  // Check to make sure 0 < i < grid_size
  if (i >= w * h or i < 0)
    return -1;


  if ((x + rel_x) >= w)
    x -= (w - 1);
  else if ((x + rel_x) < 0)
    x += (w - 1);
  else
    x += rel_x;

  if ((y + rel_y) >= h)
    y -= (h - 1);
  else if ((y + rel_y) < 0)
    y += (h - 1);
  else
    y += rel_y;

  retVal = index(y, x);
  bool outOfRange = retVal < 0 || retVal >= w * h;
  return outOfRange ? -1 : retVal;
}

//
// Convert row/col values into an array index
//
int  Grid::index( int  row, int  col )  const
{
  return  row * m_numCols + col;
}


//
// Copy constructor
//
// This uses a "deep" copy scheme so that each grid
// object contains it's own set of cell data.
//
Grid::Grid( const Grid  &rhs )
{
  copy(rhs);
}


//
// Assignment operator
//
// This uses a "deep" assignment scheme so that each grid
// object contains it's own set of cell data.
//
const Grid  &Grid::operator=( const Grid  &rhs )
{
  if  ( this != &rhs )
  {
    cleanup();

    copy(rhs);
  }


  return  *this;
}


void  Grid::copy( const Grid  &rhs )
{
  m_numRows  =  rhs.m_numRows;
  m_numCols  =  rhs.m_numCols;

  m_cells  =  new  bool[ m_numRows * m_numCols ];

  if  (! m_cells)
    exit(EXIT_FAILURE);


  //
  // Copies the cell states from the original to this object.
  //
  for( int  idx = 0;  idx < m_numRows * m_numCols;  ++idx )
    m_cells[idx]  =  rhs.m_cells[idx];
}

