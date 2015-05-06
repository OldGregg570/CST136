/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #3
 * File        :  array.h
 * Description :  Declarations for the Array template.
 *********************************************************************/
#include <stdlib.h>
#include <string.h>
#include "refCounter.h"

#ifndef  array_H
#define  array_H

/*
 * Constraints for the TYPE datatype for the Array<> template class:
 *
 *   - TYPE must support sizeof
 *   - TYPE must support assignment
 */
template<class TYPE>
class Array
{
public:

  Array(int upper, int lower=0);
  Array(const Array &rhs);

  ~Array() { if ( m_ref_count.onlyInstance() ) delete [] m_data; };

  void set(int index, TYPE value);
  const TYPE get(int index) const;

  TYPE &at(int index) { return m_data[index - m_lower]; };

  const int lowerBound() const { return m_lower; };
  const int upperBound() const { return m_upper; };

  const int numElements() const { return m_upper - m_lower + 1; };
  const int size() const { return ( sizeof *m_data) * numElements(); };

  static void set_exit(bool exit) { m_exit = exit; };

protected:
  const void err_exit(const char* message);

private:
  int m_upper;
  int m_lower;
  TYPE *m_data;
  static bool m_exit;
  RefCounter m_ref_count;
};

/*
 * Constraints for the TYPE datatype for the SafeArray<> template class:
 *
 *   - TYPE must support sizeof
 *   - TYPE must support assignment
 */
template<class TYPE>
class SafeArray : public Array<TYPE>
{
public:
  SafeArray(int upper, int lower=0) : Array<TYPE>(upper, lower) {};

  void set(int index, TYPE value);
  const TYPE get(int index);

private:
  const bool in_bounds(int index) { return !(index < Array<TYPE>::lowerBound() || index > Array<TYPE>::upperBound()); }

};

#include "array.inc"
#endif