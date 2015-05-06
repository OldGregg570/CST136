
//
// CST 136 - Assignment #2 (test program)
//
// Michael Hoffman
//
//
// File: test.cpp
//
// Test program for the Array and SafeArray classes.
//


#include  <math.h>
#include  <iostream>
#include  "array.h"
#include "refCounter.h"
using  namespace  std;


//
// Test valid limits for an Array object with a
// lower index of zero.
//
static void  zeroBasedArrayTest()
{
    Array<int>  data(5);

    data.set(0, 10);
    data.set(3, 20);
    data.set(5, 30);

    cout  <<  std::endl
    <<  "Test1 - "
    <<  data.get(0)  <<  ' '
    <<  data.get(3)  <<  ' '
    <<  data.get(5)  <<  ' '
    <<  std::endl;
}


//
// Test valid limits for an Array object with a
// non-zero, positve lower index.
//
static void  positiveBasedArrayTest()
{
    Array<int>  data(10, 5);

    data.set(5, -10);
    data.set(8, 22);
    data.set(10, 9);

    cout  <<  std::endl
    <<  "Test2 - "
    <<  data.get(5)  <<  ' '
    <<  data.get(8)  <<  ' '
    <<  data.get(10)  <<  ' '
    <<  std::endl;
}


//
// Test valid limits for an Array object with a
// non-zero, negative lower index.
//
static void  negativeBasedArrayTest()
{
    Array<int>  data(3, -2);

    data.set(-2, 78);
    data.set(0, -30);
    data.set(3, -8);

    cout  <<  std::endl
    <<  "Test3 - "
    <<  data.get(-2)  <<  ' '
    <<  data.get(0)  <<  ' '
    <<  data.get(3)  <<  ' '
    <<  std::endl;
}


//
// Display array settings and contents.
//
static void  displayArray( const Array<int>  &a, const char  *prompt )
{
    cout  <<  prompt  <<  ":"
    <<  "  L: "  <<  a.lowerBound()
    <<  "  U: "  <<  a.upperBound()
    <<  "  N: "  <<  a.numElements()
    <<  "  S: "  <<  a.size()
    <<  endl  <<  "    Contents: ";

    for(int idx = a.lowerBound();  idx <= a.upperBound();  ++idx )
        cout  <<  a.get(idx)  <<  ' ';

    cout  <<  endl;
}


//
// Test the copy constructor for the Array class.
//
static void  cctorTest()
{
    cout  <<  std::endl  <<  "Test 4"  <<  std::endl;

    const int  lower = 7;
    const int  upper = 16;

    Array<int>  data(upper, lower);

    int  idx;

    for(idx = lower;  idx <= upper;  ++idx )
        data.set(idx, (int) pow(-2.0, idx));

    displayArray(data, "  Original");

    Array<int>  copy1(data);
    Array<int>  copy2(data);

    cout  <<  endl;
    displayArray(copy1, "  Copy 1");

    cout  <<  endl;
    displayArray(copy2, "  Copy 2");

    cout  <<  std::endl;
}


//
// Test valid limits for a SafeArray object with a
// non-zero, positive lower index.
//
static void  positiveBasedSafeArrayTest()
{
    SafeArray<int>  data(10, 5);

    data.set(5, -10);
    data.set(8, 22);
    data.set(10, 9);

    cout  <<  "Test5 - "
    <<  data.get(5)  <<  ' '
    <<  data.get(8)  <<  ' '
    <<  data.get(10)  <<  ' '
    <<  std::endl;
}


//
// Test for an index limits violation for a
// SafeArray object.
//
static void  safeArrayViolationTest()
{
    SafeArray<int>  data(10, 5);

    data.set(5, -10);
    data.set(8, 22);
    data.set(10, 9);

    cout  <<  std::endl
    <<  "Test6 - "
    <<  data.get(5)  <<  ' '
    <<  data.get(8)  <<  ' '
    <<  std::endl;


    cout  <<  "  Should terminate now!"
    <<  std::endl  <<  "  ";

    cout  <<  data.get(11)  <<  std::endl;
}


//
// main() program
//
int  main()
{

    // Zero-based Array
    zeroBasedArrayTest();


    // Non-zero positive based array
    positiveBasedArrayTest();

    // Non-zero negative based array
    negativeBasedArrayTest();

    // CCTOR
    cctorTest();

    // Non-zero positive safe array
    positiveBasedSafeArrayTest();

    // Violate safe array bounds
    safeArrayViolationTest();

    cout  <<  "If you see this output, something's wrong"
    <<  std::endl;

    return  0;
}


/* Expected output

Test1 - 10 20 30

Test2 - -10 22 9

Test3 - 78 -30 -8

Test 4
  Original:  L: 7  U: 16  N: 10  S: 40
    Contents: -128 256 -512 1024 -2048 4096 -8192 16384 -32768 65536

  Copy 1:  L: 7  U: 16  N: 10  S: 40
    Contents: -128 256 -512 1024 -2048 4096 -8192 16384 -32768 65536

  Copy 2:  L: 7  U: 16  N: 10  S: 40
    Contents: -128 256 -512 1024 -2048 4096 -8192 16384 -32768 65536

Test5 - -10 22 9

Test6 - -10 22
  Should terminate now!
  Index out of range

*/