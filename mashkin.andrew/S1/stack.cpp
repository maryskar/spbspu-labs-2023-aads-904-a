#include "stack.h"
#include <cstddef>
#include <stdexcept>

template< typename T >
Stack< T >::Stack(T symb):
  stack_(new list_t< T >{symb, nullptr})
{
}

template< typename T >
void Stack< T >::push(T rhs)
{
  stack_.next = new list_t< T >{rhs, nullptr};
}

template< typename T >
void Stack< T >::pop()
{
  if (isEmpty())
  {
    throw std::underflow_error("Stack underflow");
  }
  --top_;
}

template< typename T >
T Stack< T >::drop()
{
  pop();
  return stack_[top_ + 1];
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return top_;
}
