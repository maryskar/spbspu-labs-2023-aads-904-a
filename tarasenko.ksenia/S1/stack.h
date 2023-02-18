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
 bool isEmpty();
private:
 Node< T >* top;
 size_t size;
};

template< typename T >
Stack< T >::Stack():
 top(nullptr),
 size(0)
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
bool Stack< T >::isEmpty()
{
  return size;
}

template< typename T >
void Stack< T >::push(T rhs)
{
  top = new Node< T >(rhs, top);
  size++;
}

template< typename T >
T Stack< T >::drop()
{
  Node< T >* temp = top;
  top = top->p_next;
  T temp_val = temp->value;
  delete temp;
  size--;
  return temp_val;
}

#endif
