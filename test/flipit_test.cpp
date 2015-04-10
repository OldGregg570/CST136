#include <iostream>
#include  <assert.h>
#include "../include/flipitEngine.h"

using namespace std;

int main()
{  
	
	// constructor
    FlipIt  game( 8, 7, 4, 99, FlipIt::cross_, true);
	assert( 8 == game.numRows() );
	assert( 7 == game.numCols() );

	// int numRows()
	
	
	// int numCols()
	
	
	// void click(int, int)
	game.click(2, 2);
	assert(game.fetch(2,2) == FlipIt::clear_);
	
	//  Color fetch(int, int)
	
	
	// bool done()
	
	
	cout << "\nUnit Test Success";
	
	return 0;
}



