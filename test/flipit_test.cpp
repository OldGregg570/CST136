#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "../include/flipIt.h"
#include "../include/grid.h"

#define TAB_SIZE 3

using namespace std;
typedef void (*callback_function)(void);



static int tab_depth = 0;

string _get_tabs(int depth)
{
	string str("");
	return str.insert(0, depth * TAB_SIZE, ' ');
}

void expect(int left, int right)
{
	if(left != right)
	{
		cout << _get_tabs(tab_depth + 1) << "FAIL - Assertion Error: Expected " << left << " to equal " << right << endl;
	}
	else
	{
		cout << _get_tabs(tab_depth + 1) << "PASS - Assertion SuccessS\n";
	}
}

void describe(string description, callback_function cb)
{
	cout << _get_tabs(tab_depth) << description << endl;
	tab_depth++;
	if (cb)	cb();
	tab_depth--;
}
void (&it)(string description, callback_function cb) = describe;








int main()
{
	bool passing = true;


	/**
 	* Testing getNeighborIndex(int, int, int)
	*/

	describe("FlipIt class tests", []() {
		describe("FlipIt constructor tests", []() {
			it("should have 3 rows and 4 columns", []() {
				FlipIt game( 3, 4, 4, 99, FlipIt::cross_, true);
				expect(3, game.numRows());
				expect(4, game.numCols());
			});
		});
		describe("Grid constructor tests", []() {
			it("testing wrapped visit from all possible directions to index zero.", [](){
				Grid g(3, 4);
				expect(0, g.getWrappedNeighborIndex( 0,  0,  0 ));
				expect(0, g.getWrappedNeighborIndex( 1, -1,  0 ));
				expect(0, g.getWrappedNeighborIndex( 3,  1,  0 ));
				expect(0, g.getWrappedNeighborIndex( 4,  0, -1 ));
				expect(0, g.getWrappedNeighborIndex( 5, -1, -1 ));
				expect(0, g.getWrappedNeighborIndex( 7,  1, -1 ));
				expect(0, g.getWrappedNeighborIndex( 8,  0,  1 ));
				expect(0, g.getWrappedNeighborIndex( 9, -1,  1 ));
				expect(0, g.getWrappedNeighborIndex( 11, 1,  1 ));
			});
		});
	});
	//


	//game.click(2, 2);
	//passing &=		FlipIt::clear_ == 	game.fetch(2,2);

	if (passing) {
		cout << "SUCCESS\n";
		return 0;
	}
	else {
		cout << "SUCCESS\n";
		return 0;
	}
}



