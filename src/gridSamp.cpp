
//
// CST 136 - Grid client example
//
// Author: Michael Hoffman
//
// File: simpleGrid.cpp
//
// This file contains a simple client program to illustrate
// the use of the Grid class.
//


#define  _CRT_SECURE_NO_DEPRECATE


#include  "grid.h"
#include  <iostream>
#include  <string>

using  namespace std;


#define  INPUT_SZ  80

#define  NUM_ROWS   5
#define  NUM_COLS   10

#define  CHAR_SET  'X'
#define  CHAR_CLR  '.'



//
// Display a grid
//
static void  display( const Grid  &grid )
{
  cout  <<  endl
        <<  grid.numRows()  <<  " rows, "  <<  grid.numCols()  <<  " columns."
        <<  endl  <<  endl;

  //
  // Display each grid row
  //
  for( int  row = 0;  row < grid.numRows();  ++row )
  {
    //
    // Display each column within the row
    //
    for( int  col = 0;  col < grid.numCols();  ++ col )
    {
      cout  <<  ' '  <<  ( grid.fetch(row, col)  ?  CHAR_SET  :  CHAR_CLR );
    }

    cout  <<  endl;
  }
}


//
// Prompt the user for a row/col cell choice. The
// enter values are validated. Returns true if valid
// data is entered. Returns false if no data was entered.
//
static bool  getUsersCellChoice( const Grid  &grid,
                                 int         &userRow,
                                 int         &userCol )
{
  //
  // Loop until value data is entered
  //
  while( true )
  {
    //
    // Display prompt and get user's input
    //
    cout  <<  endl  <<  "Enter row,col to toggle (zero-based, blank entry exits): ";

    char  input[INPUT_SZ];

    cin.getline( input, INPUT_SZ );


    //
    // Determine if a blank line was entered
    //
    if  ( ! strlen(input) )  return  false;


    //
    // Make sure the user entered data in the correct format
    //
    const char  *rowStr  =  strtok( input, "," );
    const char  *colStr  =  strtok( 0, "" );

    if  ( ! rowStr  ||  ! colStr )
    {
      cout  <<  endl  <<  "*** Invalid input format"  <<  endl;
      continue;
    }


    //
    // Validate the values the user entered
    //
    userRow  =  atoi( rowStr );
    userCol  =  atoi( colStr );

    if  ( userRow >= 0  &&  userRow < grid.numRows()  &&
          userCol >= 0  &&  userCol < grid.numCols() )
      break;


    //
    // Bad values entered
    //
    cout  <<  endl  <<  "*** Invalid value(s)"  <<  endl;
  };


  return  true;
}


//
// Main program
//
int  main()
{
  //
  // Create the grid
  //
  Grid  grid(NUM_ROWS, NUM_COLS);


  while( true )
  {
    //
    // Display the grid
    //
    display( grid );


    //
    // Get the current player's cell choice
    //
    int  userRow;
    int  userCol;

    if  ( ! getUsersCellChoice( grid, userRow, userCol ) )
      break;


    //
    // Toggle the grid cell the user specified
    //
    if  ( grid.fetch(userRow, userCol) )
      grid.clear( userRow, userCol );
    else
      grid.set( userRow, userCol );
  }

  return  0;
}
