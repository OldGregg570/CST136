/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #1
 * File        :  flipit.spec.cpp
 * Description :  flipit test spec. Uses catch as testing framework.
 *********************************************************************/

#define CATCH_CONFIG_MAIN
#define private public

#include "../include/flipIt.h"
#include "../lib/catch.hpp"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * Public methods
 */
TEST_CASE("class constructor and getters should initialize the board", "[FlipIt]") {
    FlipIt game(3, 3, 0, 1, FlipIt::square_, true);
    REQUIRE(3 == game.numCols());
    REQUIRE(3 == game.numRows());

    SECTION("grid should be blank", "[fetch]") {
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

TEST_CASE("all patterns should change the board as expected", "[click][fetch]") {
    SECTION("pattern: cross", "") {
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
    SECTION("pattern: x", "") {
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
    SECTION("pattern: square", "") {
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
    SECTION("pattern: hollow", "") {
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
    SECTION("pattern: corners", "") {
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

TEST_CASE("test without wrapping", "[click][fetch]") {
    SECTION("click test (0, 0)", "[]") {
        FlipIt game(3, 3, 0, 0, FlipIt::square_, false);
        game.click(0, 0);
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(0, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 2));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 2));

        game.click(2, 2);
        REQUIRE(FlipIt::solid_ == game.fetch(0, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(0, 1));
        REQUIRE(FlipIt::clear_ == game.fetch(0, 2));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 0));
        REQUIRE(FlipIt::clear_ == game.fetch(1, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(1, 2));
        REQUIRE(FlipIt::clear_ == game.fetch(2, 0));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 1));
        REQUIRE(FlipIt::solid_ == game.fetch(2, 2));
    };
};

TEST_CASE("done should return true if all cells are clear", "[click][done]") {
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


/**
 * Private methods
 */
TEST_CASE("neighbor_ tests should return neighbor indecies with or without wrapping", "[neighbor_x][neighbor_y]") {
    SECTION("neighbor_ tests", "[]") {
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
        SECTION("testing 1D neighbor_ (no actual wrapping)", "[]") {
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
        SECTION("testing 1D neighbor_ (with wrapping)", "[]") {
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

TEST_CASE("test cell toggle", "[toggle]") {
    SECTION("toggle all cells on and off", "") {
        FlipIt game(3, 3, 0, 0, FlipIt::corners_, true);
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                game.toggleCell(y, x);
                REQUIRE(FlipIt::solid_ == game.fetch(y, x));
                game.toggleCell(y, x);
                REQUIRE(FlipIt::clear_ == game.fetch(y, x));
            }
        }
    };
};