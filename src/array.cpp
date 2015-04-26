/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #2
 * File        :  array.cpp
 * Description :  Array implementation.
 *********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "array.h"

using  namespace  std;
const char* ALLOC_ERROR = "Error: memory allocation failure";

// If true, the program will exit if the Array indecies are misused
// Had to create this for now to make this program testable.
// TODO: add exception handling
bool Array::m_exit = true;

/**********************************************************************
 * Print the error message passed in and exit the program if the array
 * is configured to exit on errors.
 *********************************************************************/
const void Array::err_exit(const char* message)
{
    cerr << message << endl;
    if (Array::m_exit)
        exit(EXIT_FAILURE);
}

/**********************************************************************
 * Array constructor. specify lower and upper bound index values.
 * The lower bound index is defaulted to zero. The upper bound does
 * not have a default value. Bounds can be positive or negative.
 * The lower bound index must be less-than-or-equal-to the upper
 * bound index. An error is displayed and the program terminated
 * if this is not the case.
 *********************************************************************/
Array::Array(int upper, int lower):
        m_upper(upper),
        m_lower(lower)
{
    m_data = new (std::nothrow) ELEMENT_TYPE [upper - lower];
    if (!m_data) err_exit(ALLOC_ERROR);
};

/**********************************************************************
 * a deep-copy copy constructor.
 *********************************************************************/
Array::Array(const Array &rhs) :
        m_upper(rhs.m_upper),
        m_lower(rhs.m_lower),
        m_data(new ELEMENT_TYPE[rhs.m_upper - rhs.m_lower])
{

    memcpy(m_data, rhs.m_data, rhs.size());
    if (!m_data)
        err_exit(ALLOC_ERROR);
}

/**********************************************************************
 * place an element value at a specific index position in the array.
 *********************************************************************/
void Array::set(int index, ELEMENT_TYPE value)
{
    m_data[index - m_lower] = value;
};


/**********************************************************************
 * fetch an element value from a specific index position within
 * the array.
 *********************************************************************/
const ELEMENT_TYPE Array::get(int index)
{
    return m_data[index - m_lower];
};

/**********************************************************************
 * place an element value at a specific index position in the array.
 * If index is out of bounds, outputs an error message and exits.
 *********************************************************************/
void SafeArray::set(int index, ELEMENT_TYPE value)
{
    if (in_bounds(index))
        Array::set(index, value);
    else
        err_exit("Error: Index out of bounds");
};

/**********************************************************************
 * fetch an element value from a specific index position within
 * the array. If index is out of bounds, outputs an error message
 * and exits.
 *********************************************************************/
const ELEMENT_TYPE SafeArray::get(int index)
{
    if (in_bounds(index))
        return Array::get(index);
    else
        err_exit("Error: Index out of bounds. Returning index zero.");
        return Array::get(0);
};