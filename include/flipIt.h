
//
// Assignment  :  #1
// Class       :  CST 136
//
// Author      :  Andrew Bragg
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
  public:
    enum  Color  { clear_ = false, solid_ = true };
    enum  Pattern  { cross_, x_, square_, hollowSquare_, corners_ };

    FlipIt( int      nRows,
            int      nCols,
            int      gameNum,
            int      complexity,
            Pattern  pattern,
            bool     wrap );

    int  numRows()  const;
    int  numCols()  const;

    void  click( int  row, int  col );

    Color   fetch( int  row, int  col ) const;

    bool    done() const;

  private:
	Grid        m_grid;
    Pattern     m_pattern;
    bool        m_wrap;
    void        toggleSquare ( int row, int col );
    int*        getPatternMatrix();
};

#endif