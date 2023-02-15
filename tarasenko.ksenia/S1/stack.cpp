#include "stack.h"

template< typename T >
void Stack<T>::push(T &rhs)
{
  top = new Node<T>(rhs, top);
}

template< typename T >
T& Stack< T >::drop()
{
  Node< T >* temp = top;
  top = top->p_next;
  return temp;
}
