#include <iostream>
#include<string.h>
#include  <assert.h>
#include "../include/flipIt.h"
#include "../include/grid.h"

using namespace std;
typedef void (*callback_function)(void);


void expect(int left, int right)
{
	if(left != right)
	{
		cout << "Expected " << left << " to equal " << right << endl;
	}
}

string _get_tabs(int depth)
{
	string str("");
	return str.insert(0, depth, '\t');
}

void it(string description, callback_function cb)
{
	static int tab_depth = 0;
	string tabs = _get_tabs(tab_depth);
	cout << tabs << description << endl;
	if (cb)
	{
		it_depth++;
		cb();
	}

	it_depth--;
	return;
}


int main() {
	bool passing = true;

    FlipIt game( 3, 4, 4, 99, FlipIt::cross_, true);
	/**
	 * Testing FlipIt::numRows() and FlipIt::numCols() after construction
	 */
	passing &= 		3 == 				game.numRows();
	passing &= 		4 == 				game.numCols();

	/**
 	* Testing getNeighborIndex(int, int, int)
	*/
	Grid g(3, 4);

	it("Test 1", []()
	{
		it("Test 2", []()
		{
			it("Test 3", []()
			{
			});
		});
	});
	//expect(0, g.getWrappedNeighborIndex( 0,  0,  0 ));
	//expect(0, g.getWrappedNeighborIndex( 1, -1,  0 ));
	//expect(0, g.getWrappedNeighborIndex( 3,  1,  0 ));
	//expect(0, g.getWrappedNeighborIndex( 4,  0, -1 ));
	//expect(0, g.getWrappedNeighborIndex( 5, -1, -1 ));
	//expect(0, g.getWrappedNeighborIndex( 7,  1, -1 ));
	//expect(0, g.getWrappedNeighborIndex( 8,  0,  1 ));
	//expect(0, g.getWrappedNeighborIndex( 9, -1,  1 ));
	//expect(0, g.getWrappedNeighborIndex( 11, 1,  1 ));


	game.click(2, 2);
	passing &=		FlipIt::clear_ == 	game.fetch(2,2);

	if (passing) {
		cout << "SUCCESS\n";
		return 0;
	}
	else {
		cout << "SUCCESS\n";
		return 1;
	}
}



