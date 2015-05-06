/**********************************************************************
 * Author      :  Andrew Bragg
 * Class       :  CST 136
 * Assignment  :  #3
 * File        :  refCounter.h
 * Description :  refCounter class from lecture notes.
 *********************************************************************/
#ifndef  refCounter_H
#define  refCounter_H

class RefCounter
{
public:
    RefCounter();
    RefCounter(const RefCounter  &rhs);
    ~RefCounter();
    bool  onlyInstance() const { return *m_count == 1; };

private:
    int *m_count;
};


#endif
