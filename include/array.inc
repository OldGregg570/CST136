/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #3
 * File        :  array.inc
 * Description :  Shallow copy array implementation.
 *********************************************************************/

#define ALLOC_ERROR "Error: memory allocation failure"

#include <iostream>
#include <stdlib.h>

using  namespace  std;

// If true, the program will exit if the Array indecies are misused
// Had to create this for now to make this program testable.
// TODO: add exception handling
template<class TYPE>
bool Array<TYPE>::m_exit = true;

/**********************************************************************
 * Print the error message passed in and exit the program if the array
 * is configured to exit on errors.
 *********************************************************************/
template<class TYPE>
const void Array<TYPE>::err_exit(const char* message)
{
    cerr << message << endl;
    if (Array::m_exit) exit(EXIT_FAILURE);
}

/**********************************************************************
 * Array constructor. specify lower and upper bound index values.
 * The lower bound index is defaulted to zero. The upper bound does
 * not have a default value. Bounds can be positive or negative.
 * The lower bound index must be less-than-or-equal-to the upper
 * bound index. An error is displayed and the program terminated
 * if this is not the case.
 *********************************************************************/
template<class TYPE>
Array<TYPE>::Array(int upper, int lower): m_upper(upper), m_lower(lower)
{
    m_data = new (std::nothrow) TYPE [upper - lower];
    if (!m_data) err_exit(ALLOC_ERROR);
};

/**********************************************************************
 * a shallow-copy copy constructor.
 *********************************************************************/
template<class TYPE>
Array<TYPE>::Array(const Array &rhs) :
        m_upper(rhs.m_upper), m_lower(rhs.m_lower), m_data(rhs.m_data) { }

/**********************************************************************
 * place an element value at a specific index position in the array.
 *********************************************************************/
template<class TYPE>
void Array<TYPE>::set(int index, TYPE value)
{
    m_data[index - m_lower] = value;
};


/**********************************************************************
 * fetch an element value from a specific index position within
 * the array.
 *********************************************************************/
template<class TYPE>
const TYPE Array<TYPE>::get(int index) const
{
    return m_data[index - m_lower];
};

/**********************************************************************
 * place an element value at a specific index position in the array.
 * If index is out of bounds, outputs an error message and exits.
 *********************************************************************/
template<class TYPE>
void SafeArray<TYPE>::set(int index, TYPE value)
{
    if (in_bounds(index))
        Array<TYPE>::set(index, value);
    else
        Array<TYPE>::err_exit("Error: Index out of bounds");
};

/**********************************************************************
 * fetch an element value from a specific index position within
 * the array. If index is out of bounds, outputs an error message
 * and exits.
 *********************************************************************/
template<class TYPE>
const TYPE SafeArray<TYPE>::get(int index)
{
    if (in_bounds(index))
        return Array<TYPE>::get(index);
    else
        Array<TYPE>::err_exit("Error: Index out of bounds. Returning index zero.");
        return Array<TYPE>::get(0);
};