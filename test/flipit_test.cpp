#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "../include/flipIt.h"
#include "../include/grid.h"

#define TAB_SIZE 3

using namespace std;
typedef void (*callback_function)(void);


// TODO: turn all oft his into a class
static int tab_depth = 0;
static bool g_passing = true;
string _get_tabs(int depth) {
	string str("");
	return str.insert(0, depth * TAB_SIZE, ' ');
}

void expect(int left, int right) {
	bool pass = left == right;
	if(pass)
		cout << _get_tabs(tab_depth + 1) << "PASS - Assertion Success\n";
	else
		cout << _get_tabs(tab_depth + 1) << "FAIL - Assertion Error: Expected " << left << " to equal " << right << endl;

	g_passing &= pass;
}

void describe(string description, callback_function cb) {
	cout << _get_tabs(tab_depth) << description << endl;
	tab_depth++;
	if (cb)	cb();
	tab_depth--;
}

void (&it)(string description, callback_function cb) = describe;

// TODO: beforeEach






int main()
{
	int SEED = 4;
	/**
 	* Testing getNeighborIndex(int, int, int)
	*/
	describe("Grid constructor tests", []() {
		it("testing wrapped visit from all possible directions to index zero.", []() {
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
		it("testing other cases", []() {
			Grid g(10, 10);
			expect(4, g.getWrappedNeighborIndex(14, 0, -1));
			expect(5, g.getWrappedNeighborIndex(95, 0, 1));
			expect(6, g.getWrappedNeighborIndex(5, 1, 0));
		});
		it("bounds testing", []() {
			Grid g(2, 2);
			expect(-1, g.getWrappedNeighborIndex(-1, 0, 0));
			expect(-1, g.getWrappedNeighborIndex(-1, 1, 0));
			expect(-1, g.getWrappedNeighborIndex(-2, 0, 0));
			expect(-1, g.getWrappedNeighborIndex(4, 0, 0));
		});
	});
	describe("FlipIt class tests", []() {
		describe("FlipIt constructor/getter tests", []() {
			it("should have 3 rows and 4 columns", []() {
				FlipIt game( 3, 4, SEED, 1, FlipIt::cross_, true);
				expect(3, game.numRows());
				expect(4, game.numCols());
			});
		});
		describe("click test", [](){
			it("", [](){
				FlipIt game( 3, 4, SEED, 1, FlipIt::cross_, true);

			});
		});
	});

	if (g_passing) { return 0; }
	else { return -1; }
}
