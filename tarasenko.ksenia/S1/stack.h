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
 T& getTopElem();
 void pop();
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
  return size == 0;
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
  if (!size)
  {
    throw std::underflow_error("Underflow!\n");
  }
  Node< T >* temp = top;
  top = top->p_next;
  T temp_val = temp->value;
  delete temp;
  size--;
  return temp_val;
}

template< typename T >
T& Stack< T >::getTopElem()
{
  if (!size)
  {
    throw std::underflow_error("Underflow!\n");
  }
  return top->value;
}

template< typename T >
void Stack< T >::pop()
{
  if (!size)
  {
    throw std::underflow_error("Underflow!\n");
  }
  Node< T >* temp = top;
  top = top->p_next;
  delete temp;
  size--;
}

#endif
