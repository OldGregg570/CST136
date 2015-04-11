#define CATCH_CONFIG_MAIN
#define private public

#include "../include/flipIt.h"
#include "../lib/catch.hpp"
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

TEST_CASE("class constructor and getters should initialize the board", "[FlipIt]") {
    FlipIt game(3, 3, 0, 1, FlipIt::square_, true);
    REQUIRE(3 == game.numCols());
    REQUIRE(3 == game.numRows());

    SECTION("testing random initial board clicks", "[game.fetch()") {
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 2));
    };
};
TEST_CASE("all patterns should change the board as expected", "") {
    SECTION("pattern: cross", "[game.fetch()]") {
        FlipIt game(3, 3, 0, 0, FlipIt::cross_, true);
        game.click(1, 1);
        REQUIRE(FlipIt::clear_ == game.fetch(0, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(0, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 2));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 2));
    };
    SECTION("pattern: x", "[game.fetch()]") {
        FlipIt game(3, 3, 0, 0, FlipIt::x_, true);
        game.click(1, 1);
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(0, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 2));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 2));
    };
    SECTION("pattern: square", "[game.fetch()]") {
        FlipIt game(3, 3, 0, 0, FlipIt::square_, true);
        game.click(1, 1);
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 2));
    };
    SECTION("pattern: hollow", "[game.fetch()]") {
        FlipIt game(3, 3, 0, 0, FlipIt::hollowSquare_, true);
        game.click(1, 1);
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 2));
    };
    SECTION("pattern: corners", "[game.fetch()]") {
        FlipIt game(3, 3, 0, 0, FlipIt::corners_, true);
        game.click(1, 1);
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(0, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 2));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 2));
    };
};

TEST_CASE("fetch should return cell state", "[game.fetch()]") {
    SECTION("fetch test", "[]") {
        SECTION("", "[]") {
            FlipIt game(3, 4, 4, 1, FlipIt::cross_, true);
        };
    };
};
TEST_CASE("done should return true if all cells are clear", "[game.done()]") {
    SECTION("done test", "[]") {
        FlipIt game(3, 3, 0,0, FlipIt::cross_, true);
        SECTION("testing done true and false", "[]") {
            game.click(1, 1);
            REQUIRE(false == game.done());
            game.click(1, 1);
            REQUIRE(true == game.done());
            game.click(1, 1);
            REQUIRE(false == game.done());
        };
    };
};
TEST_CASE("getWrapped tests should return neighbor indecies with or without wrapping", "[game.neighbor_]") {
    SECTION("getWrappedNeighbor tests", "[]") {
        SECTION("testing wrapped visit from all possible directions to index zero.", "[]") {
            FlipIt g( 3, 4, 0, 0, FlipIt::cross_, true);
            REQUIRE(0 == g.neighbor_x( 0,  0 ));
            REQUIRE(0 == g.neighbor_y( 0,  0 ));
            REQUIRE(0 == g.neighbor_x( 1, -1 ));
            REQUIRE(0 == g.neighbor_y( 1,  0 ));
            REQUIRE(0 == g.neighbor_x( 3,  1 ));
            REQUIRE(0 == g.neighbor_y( 3,  0 ));
            REQUIRE(0 == g.neighbor_x( 4,  0 ));
            REQUIRE(0 == g.neighbor_y( 4,  -1 ));
            REQUIRE(0 == g.neighbor_x( 5, -1 ));
            REQUIRE(0 == g.neighbor_y( 5, -1 ));
            REQUIRE(0 == g.neighbor_x( 7,  1 ));
            REQUIRE(0 == g.neighbor_y( 7,  -1 ));
            REQUIRE(0 == g.neighbor_x( 8,  0 ));
            REQUIRE(0 == g.neighbor_y( 8,  1 ));
            REQUIRE(0 == g.neighbor_x( 9, -1 ));
            REQUIRE(0 == g.neighbor_y( 9, 1 ));
            REQUIRE(0 == g.neighbor_x( 11, 1 ));
            REQUIRE(0 == g.neighbor_y( 11, 1 ));
        };
        SECTION("testing 1D getWrapped_ (no actual wrapping)", "[]") {
            FlipIt g( 3, 3, 0, 0, FlipIt::corners_, true);
            REQUIRE(1 == g.neighbor_x(7, 0));
            REQUIRE(1 == g.neighbor_x(3, 1));
            REQUIRE(1 == g.neighbor_x(5, -1));
            REQUIRE(1 == g.neighbor_x(1, 0));
            REQUIRE(1 == g.neighbor_y(7, -1));
            REQUIRE(1 == g.neighbor_y(3, 0));
            REQUIRE(1 == g.neighbor_y(5, 0));
            REQUIRE(1 == g.neighbor_y(1, 1));
        };
        SECTION("testing 1D getWrapped_ (with wrapping)", "[]") {
            FlipIt g( 3, 3, 0, 0, FlipIt::corners_, true);
            REQUIRE(0 == g.neighbor_x(2, 1));
            REQUIRE(0 == g.neighbor_x(5, 1));
            REQUIRE(0 == g.neighbor_x(8, 1));
            REQUIRE(0 == g.neighbor_y(6, 1));
            REQUIRE(0 == g.neighbor_y(7, 1));
            REQUIRE(0 == g.neighbor_y(8, 1));
        };
    };
};
