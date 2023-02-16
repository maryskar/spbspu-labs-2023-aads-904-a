#ifndef STACK_H
#define STACK_H
#include "node.h"

template< typename T >
class Stack
{
public:
 Stack();
 ~Stack();
 void push(T rhs);
 T drop();
private:
 Node< T >* top;
};

template< typename T >
Stack< T >::Stack():
 top(nullptr)
{}

template< typename T >
Stack< T >::~Stack()
{
  while (top)
  {
    drop();
  }
}

template< typename T >
void Stack< T >::push(T rhs)
{
  top = new Node< T >(rhs, top);
}

template< typename T >
T Stack< T >::drop()
{
  Node< T >* temp = top;
  top = top->p_next;
  T temp_val = temp->value;
  delete temp;
  return temp_val;
}

#endif
