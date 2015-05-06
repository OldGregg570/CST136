/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #3
 * File        :  refCounter.h
 * Description :  refCounter implementation from lecture notes.
 *********************************************************************/

#include <stdlib.h>
#include <iostream>
#include "refCounter.h"

using namespace std;

/**********************************************************************
 * Constructor. Allocates an int with an initial value of 1.
 *********************************************************************/
RefCounter::RefCounter() : m_count(new int(1))
{
    if  (!m_count)
    {
        cerr  <<  "Memory allocation error!"  <<  endl;
        exit(EXIT_FAILURE);
    }
};

/**********************************************************************
 * Copy constructor that increments the reference count.
 *********************************************************************/
RefCounter::RefCounter(const RefCounter  &rhs) : m_count(rhs.m_count) { (*m_count)++; };

/**********************************************************************
 * Destructor that decrements the reference count.
 *********************************************************************/
RefCounter::~RefCounter() { if  (!--(*m_count)) delete m_count; };