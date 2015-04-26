/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #2
 * File        :  array_char.spec.cpp
 * Description :  array test spec
 *********************************************************************/

#define CATCH_CONFIG_MAIN

#include "array.h"
#include "../lib/catch.hpp"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <limits.h>
using namespace std;

/**
 * Type agnostic array testing
 */
TEST_CASE("robustness testing") {
    Array::set_exit(false);
    SECTION("finding upper limit on allocation") {
        cout << "\nINT_MAX elements \n<error>\n\t ";
        Array array_too_large_0(INT_MAX);
        cout << "</error>\n";
        cout << "\nINT_MAX / 2 elements \n<error>\n\t ";
        Array array_too_large_1(INT_MAX / 2);
        cout << "</error>\n";
        cout << "\nINT_MAX / 4 elements \n<error>\n\t ";
        Array array_too_large_2(INT_MAX / 4);
        cout << "</error>\n";

        cout << "\nINT_MAX / 8 elements \n<no_error> ";
        Array array_small_enough_0(INT_MAX / 8);
        cout << "</no_error>\n";
        cout << "\nINT_MAX / 16 elements \n<no_error> ";
        Array array_small_enough_1(INT_MAX / 16);
        cout << "</no_error>\n";

        cout << INT_MAX / 8 << " element array: ";
        cout << array_small_enough_0.size() << " bytes\n";

        REQUIRE(array_too_large_1.size() == 0);
    }
};

TEST_CASE("array constructor") {
    Array::set_exit(false);
    SECTION("instantiating an array with just an upper bound should set the lower bound to zero") {
        Array array(20);
        REQUIRE(array.upperBound() == 20);
        REQUIRE(array.lowerBound() == 0);
        REQUIRE(array.numElements() == 21);
    };
    SECTION("instantiating an array with an upper bound and a lower bound should set both") {
        Array array(18, 15);
        REQUIRE(array.upperBound() == 18);
        REQUIRE(array.lowerBound() == 15);
        REQUIRE(array.numElements() == 4);
    };
    SECTION("instantiating an array with negative bounds should work") {
        Array array(-5, -15);
        REQUIRE(array.upperBound() == -5);
        REQUIRE(array.lowerBound() == -15);
        REQUIRE(array.numElements() == 11);
    };
    SECTION("an array of size one is allowed in the spec") {
        Array array(0);
        // Note: There is no way to make an array of length zero
        REQUIRE(array.numElements() == 1);
    };
    SECTION("instantiating an array with upper < lower should output an error") {
        cout << "\nINT_MAX / 4 elements \n<error>\n\t ";
        Array array(1, 4);
        cout << "</error>\n";
    };
};

/**
 * Array with ints
 */
TEST_CASE("array copy constructor") {
    Array::set_exit(false);
    SECTION("copied array should have the same size as original") {
        Array array(9);
        Array array_copy(array);
        REQUIRE(array_copy.upperBound() == 9);
        REQUIRE(array_copy.lowerBound() == 0);
        REQUIRE(array_copy.numElements() == 10);
        REQUIRE(array_copy.size() == array.size());
    };
    SECTION("copied array should have the same data as original") {
        Array array(9);
        array.set(0, 10);
        array.set(1, 50);
        array.set(2, 110);
        Array array_copy(array);
        REQUIRE(array_copy.get(0) == 10);
        REQUIRE(array_copy.get(1) == 50);
        REQUIRE(array_copy.get(2) == 110);
    };
    SECTION("deep copy should let arrays to be modified independently") {
        Array array(9);
        array.set(0, 10);
        array.set(1, 50);
        array.set(2, 110);

        Array array_copy(array);
        // Modifying the copy ...
        array_copy.set(0, 15);
        array_copy.set(1, -15);
        array_copy.set(2, 155);

        // ... shouldn't change the original
        REQUIRE(array.get(0) == 10);
        REQUIRE(array.get(1) == 50);
        REQUIRE(array.get(2) == 110);

        REQUIRE(array_copy.get(0) == 15);
        REQUIRE(array_copy.get(1) == -15);
        REQUIRE(array_copy.get(2) == 155);

        // Modifying the original ...
        array.set(2, 1000);

        // ... shouldn't change the copy
        REQUIRE(array_copy.get(2) == 155);
    };
};

TEST_CASE("array.size method on array of ints (4 bytes for an int on my machine)") {
    REQUIRE(sizeof(int) == 4);
    SECTION("array with 1 int should be 4 bytes") {
        Array array(0);
        REQUIRE(4 == array.size());
    };
    SECTION("array with 1000 ints should be 4 kbytes") {
        Array array(999);
        REQUIRE(4000 == array.size());
    };
};

TEST_CASE("array.get and array.set methods") {
    Array::set_exit(false);
    SECTION(".setting an element should make it .gettable") {
        Array array(20);
        for (int i = 0; i < 10; i++) {
            array.set(i, i + 1);
        }
        for (int i = 0; i < 10; i++) {
            REQUIRE (array.get(i) == i + 1);
        }
    };

    SECTION("testing with negative bounds") {
        Array array(-20, -30);
        for (int i = -30; i < -20; i++) {
            array.set(i, i + 1);
        }
        for (int i = -30; i < -20; i++) {
            REQUIRE (array.get(i) == i + 1);
        }
    };
};

/**
 * SafeArray with ints
 */

TEST_CASE("SafeArray should work with ints") {
    Array::set_exit(false);
    SECTION("SafeArray constructor") {
        SafeArray array(9);
        REQUIRE(array.upperBound() == 9);
        array.set(0, 5);
        REQUIRE(array.get(0) == 5);
    };
    SECTION("SafeArray copy constructor") {
        SafeArray array(9);
        SafeArray copy(array);
        REQUIRE(copy.upperBound() == 9);
        copy.set(0, 5);
        REQUIRE(copy.get(0) == 5);
    };
    SECTION("SafeArray bounds checking") {
        SafeArray array(9);
        array.set(0, 42);
        array.set(9, 42);

        REQUIRE(array.get(0) == 42);
        REQUIRE(array.get(9) == 42);

        cout << "\narray.get(-1) == 42 \n<error>\n\t ";
        REQUIRE(array.get(-1) == 42);
        cout << "</error>\n";

        cout << "\narray.get(10) == 42 \n<error>\n\t ";
        REQUIRE(array.get(10) == 42);
        cout << "</error>\n";

        cout << "\narray.set(-10, 100) \n<error>\n\t ";
        array.set(-10, 100);
        cout << "</error>\n";

        cout << "\narray.get(-10) == 42 \n<error>\n\t ";
        REQUIRE(array.get(-10) == 42);
        cout << "</error>\n";
    };
};
