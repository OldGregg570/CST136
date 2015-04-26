/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #2
 * File        :  array.h
 * Description :  Declarations for the Array class.
 *********************************************************************/

#ifndef  array_H
#define  array_H
#define ELEMENT_TYPE int

class Array
{
public:

  Array(int upper, int lower=0);
  Array(const Array &rhs);

  ~Array() { delete [] m_data; };

  void set(int index, ELEMENT_TYPE value);
  const ELEMENT_TYPE get(int index);

  const int lowerBound() { return m_lower; };
  const int upperBound() { return m_upper; };

  const int numElements() const { return m_upper - m_lower + 1; };
  const int size() const { return (sizeof *m_data) * numElements(); };

  static void set_exit(bool exit) { m_exit = exit; };

protected:
  int m_upper;
  int m_lower;
  const void err_exit(const char* message);

private:
  ELEMENT_TYPE *m_data;
  static bool m_exit;
};


class SafeArray : public Array
{
public:
  SafeArray(int upper, int lower=0) : Array(upper, lower) {};
  SafeArray(const Array &rhs) : Array(rhs) {};

  void set(int index, ELEMENT_TYPE value);
  const ELEMENT_TYPE get(int index);

private:
  const bool in_bounds(int index) {return !(index < m_lower || index > m_upper); }

};

#endif