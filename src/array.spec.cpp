/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #3
 * File        :  array.spec.cpp
 * Description :  array template test spec
 *********************************************************************/

#define CATCH_CONFIG_MAIN

#include "array.h"
#include "catch.hpp"
#include "refCounter.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <limits.h>
using namespace std;

/**
 * Type agnostic array testing
 */
TEST_CASE("robustness testing") {
    Array<int>::set_exit(false);
//    SECTION("finding approximate upper limit on allocation") {
//        Array<int> array_too_large_0(INT_MAX);
//        Array<int> array_too_large_1(INT_MAX / 2);
//        Array<int> array_too_large_2(INT_MAX / 4);
//        Array<int> array_small_enough_0(INT_MAX / 8);
//        Array<int> array_small_enough_1(INT_MAX / 16);
//
//        cout << INT_MAX / 8 << " element array: ";
//        cout << array_small_enough_0.size() << " bytes\n";
//    }
};

TEST_CASE("array constructor") {
    Array<int>::set_exit(false);
    SECTION("instantiating an array with just an upper bound should set the lower bound to zero") {
        Array<int> array(20);
        REQUIRE(array.upperBound() == 20);
        REQUIRE(array.lowerBound() == 0);
        REQUIRE(array.numElements() == 21);
    };
    SECTION("instantiating an array with an upper bound and a lower bound should set both") {
        Array<int> array(18, 15);
        REQUIRE(array.upperBound() == 18);
        REQUIRE(array.lowerBound() == 15);
        REQUIRE(array.numElements() == 4);
    };
    SECTION("instantiating an array with negative bounds should work") {
        Array<int> array(-5, -15);
        REQUIRE(array.upperBound() == -5);
        REQUIRE(array.lowerBound() == -15);
        REQUIRE(array.numElements() == 11);
    };
    SECTION("an array of size one is allowed in the spec") {
        Array<int> array(0);
        // Note: There is no way to make an array of length zero
        REQUIRE(array.numElements() == 1);
    };
    SECTION("instantiating an array with upper < lower should output an error") {
        Array<int> array(1, 4);
        // No way to check the output of cerr to tell if error happened
    };
};

/**
 * Array<int> with 4-byte ints
 */
TEST_CASE("array copy constructor") {
    Array<int>::set_exit(false);
    SECTION("copied array should have the same size as original") {
        Array<int> array(9);
        Array<int> array_copy(array);
        REQUIRE(array_copy.upperBound() == 9);
        REQUIRE(array_copy.lowerBound() == 0);
        REQUIRE(array_copy.numElements() == 10);
        REQUIRE(array_copy.size() == array.size());
    };
    SECTION("copied array should have the same data as original") {
        Array<int> array(9);
        array.set(0, 10);
        array.set(1, 50);
        array.set(2, 110);
        Array<int> array_copy(array);
        REQUIRE(array_copy.get(0) == 10);
        REQUIRE(array_copy.get(1) == 50);
        REQUIRE(array_copy.get(2) == 110);
    };
    SECTION("shallow copy should not let arrays be modified independently") {
        Array<int> array(9);
        array.set(0, 10);
        array.set(1, 50);
        array.set(2, 110);

        Array<int> array_copy(array);
        // Modifying the copy ...
        array_copy.set(0, 15);
        array_copy.set(1, -15);
        array_copy.set(2, 155);

        // ... should change the original
        REQUIRE(array.get(0) == 15);
        REQUIRE(array.get(1) == -15);
        REQUIRE(array.get(2) == 155);

        REQUIRE(array_copy.get(0) == 15);
        REQUIRE(array_copy.get(1) == -15);
        REQUIRE(array_copy.get(2) == 155);

        // Modifying the original ...
        array.set(2, 200);

        // ... should change the copy
        REQUIRE(array_copy.get(2) == 200);
    };
};

TEST_CASE("array.size method on array of ints (4 bytes for an int on my machine)") {
    REQUIRE(sizeof(int) == 4);
    SECTION("array with 1 int should be 4 bytes") {
        Array<int> array(0);
        REQUIRE(4 == array.size());
    };
    SECTION("array with 1000 ints should be 4 kbytes") {
        Array<int> array(999);
        REQUIRE(4000 == array.size());
    };
};

TEST_CASE("array.get and array.set methods") {
    Array<int>::set_exit(false);
    SECTION(".setting an element should make it .gettable") {
        Array<int> array(20);
        for (int i = 0; i < 10; i++) {
            array.set(i, i + 1);
        }
        for (int i = 0; i < 10; i++) {
            REQUIRE (array.get(i) == i + 1);
        }
    };

    SECTION("testing with negative bounds") {
        Array<int> array(-20, -30);
        for (int i = -30; i < -20; i++) {
            array.set(i, i + 1);
        }
        for (int i = -30; i < -20; i++) {
            REQUIRE (array.get(i) == i + 1);
        }
    };
};

/**
 * SafeArray<int> with ints
 */
TEST_CASE("SafeArray<int> should work with ints") {
    Array<int>::set_exit(false);
    SECTION("SafeArray<int> constructor") {
        SafeArray<int> array(9);
        REQUIRE(array.upperBound() == 9);
        array.set(0, 5);
        REQUIRE(array.get(0) == 5);
    };
    SECTION("SafeArray<int> copy constructor") {
        SafeArray<int> array(9);
        SafeArray<int> copy(array);
        REQUIRE(copy.upperBound() == 9);
        copy.set(0, 5);
        REQUIRE(copy.get(0) == 5);
    };
    SECTION("SafeArray<int> bounds checking") {
        SafeArray<int> array(9);
        array.set(0, 42);
        array.set(9, 42);

        REQUIRE(array.get(0) == 42);
        REQUIRE(array.get(9) == 42);

        REQUIRE(array.get(-1) == 42);
        REQUIRE(array.get(10) == 42);
        array.set(-10, 100);
        REQUIRE(array.get(-10) == 42);
    };
};

TEST_CASE("Array<int> .at() method") {
    Array<int>::set_exit(false);
    SECTION("Array .at tests") {
        Array<int> array(9);
        array.at(4) = 2;
        REQUIRE(array.at(4) == 2);
    };
};


TEST_CASE("Array of RefCounter objects") {
    Array<RefCounter>::set_exit(false);
    SECTION("Array .at tests") {
        Array<RefCounter> array(9);
        RefCounter r;
        array.at(0) = r;
        REQUIRE( array.at(0).onlyInstance() == true);

        RefCounter cpy = RefCounter(array.at(0));
        array.at(1) = cpy;
        REQUIRE( array.at(1).onlyInstance() == false);
    };
};


TEST_CASE("Prof. Hoffman's test cases") {
    Array<int>::set_exit(false);
    SECTION("zero based array") {
        Array<int> data(5);

        data.set(0, 10);
        data.set(3, 20);
        data.set(5, 30);

        REQUIRE(10 == data.get(0));
        REQUIRE(20 == data.get(3));
        REQUIRE(30 == data.get(5));
    };

    SECTION("positive based array") {
        Array<int> data(10, 5);

        data.set(5, -10);
        data.set(8, 22);
        data.set(10, 9);

        REQUIRE(-10 == data.get(5));
        REQUIRE(22 == data.get(8));
        REQUIRE(9 == data.get(10));
    };

    SECTION("negative based array test") {
        Array<int> data(3, -2);

        data.set(-2, 78);
        data.set(0, -30);
        data.set(3, -8);

       REQUIRE(78 == data.get(-2));
       REQUIRE(-30 == data.get(0));
       REQUIRE(-8 == data.get(3));
    };

    SECTION("cctor test")
    {
        const int  lower = 7;
        const int  upper = 16;

        Array<int>  data(upper, lower);

        int  idx;

        for(idx = lower;  idx <= upper;  ++idx )
            data.set(idx, (int) pow(-2.0, idx));

        Array<int> copy1(data);
        Array<int> copy2(data);

        for(idx = lower;  idx <= upper;  ++idx )
        {
            REQUIRE((int) pow(-2.0, idx) == data.get(idx));
            REQUIRE((int) pow(-2.0, idx) == copy1.get(idx));
            REQUIRE((int) pow(-2.0, idx) == copy2.get(idx));
        }
    ;}
};


