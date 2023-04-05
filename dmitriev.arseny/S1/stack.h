#ifndef STACK_H
#define STACK_H

#include "list.h"

template< typename T >
class Stack
{
public:
  Stack();
  ~Stack();

  void push(T rhs);
  T drop();

  bool isEmpty() const;
  T top() const;

private:
  List< T >* top;

};

template< typename T >
inline Stack< T >::Stack():
  top(nullptr)
{

}

template< typename T >
inline Stack< T >::~Stack()
{

}

#endif
