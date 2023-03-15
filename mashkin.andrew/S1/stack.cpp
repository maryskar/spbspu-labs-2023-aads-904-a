#include "stack.h"
#include <cstddef>
#include <stdexcept>

template< typename T >
Stack< T >::Stack():
  stack_{0},
  top_(0)
{}

template< typename T >
void Stack< T >::push(T rhs)
{
  if (top_ == OVERFLOW)
  {
    throw std::overflow_error("Stackoverflow");
  }
  stack_[top_++] = rhs;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return top_;
}
