#include <iostream>
#include "../include/grid.h"

using namespace std;

int main()
{  
	cout << "Flipit Unit Tests" << "\n";
	Grid grid(4, 4);
	grid.set (2, 2);
	cout << grid.fetch(2, 2) << "\n";
	cout << grid.fetch(2, 1) << "\n";
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}



