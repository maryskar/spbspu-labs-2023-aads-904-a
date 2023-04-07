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
Stack< T >::Stack():
  top(nullptr)
{

}

template< typename T >
Stack< T >::~Stack()
{

}

template< typename T >
void Stack< T >::push(T rhs)
{
  List< T >* newTop = new List< T >(rhs, top);

  top = newTop;
}

template< typename T >
T Stack< T >::drop()
{
  return T();
}

#endif
