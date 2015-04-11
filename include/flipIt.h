
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

    int  numRows() const { return m_grid.numRows(); };
    int  numCols() const { return m_grid.numCols(); };

    void  click( int  row, int  col );

    Color   fetch(int row, int col) const { return (FlipIt::Color) m_grid.fetch(row, col); };

    bool    done() const;

  private:
    const Pattern m_pattern;
    Grid    m_grid;
    bool    m_wrap;
    void    toggleCell ( int row, int col );
    int     getWrappedNeighbor(int home, int dx, int dy) const;
    int     getWrapped_x(int home, int dx) const;
    int     getWrapped_y(int home, int dy) const;
    int*    getDirectionList();

};

#endif