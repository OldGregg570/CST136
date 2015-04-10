
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  <your name here>
//
// File        :  flipIt.h
//
//
// Description :  Declarations for the FlipIt game class.
//

#ifndef  flipit_H
#define  flipit_H


#include  "grid.h"


class  FlipIt
{
  public  :

    enum  Color  { clear_ = false, solid_ = true };

    enum  Pattern  { cross_, x_, square_, hollowSquare_, corners_ };

    FlipIt( int      nRows,
            int      nCols,
            int      gameNum,
            int      complexity,
            Pattern  pattern,
            bool     wrap );

    int  numRows()  const ;
    int  numCols()  const ;

    void  click( int  row, int  col );

    Color  fetch( int  row, int  col ) const;

    bool  done() const;

  private  :
	Grid m_grid;	
	Color m_color;
  // you get to define the private member variables/functions
};




#endif
