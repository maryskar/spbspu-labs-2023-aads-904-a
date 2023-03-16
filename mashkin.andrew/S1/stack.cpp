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
    throw std::overflow_error("Stack overflow");
  }
  stack_[top_++] = rhs;
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

template< typename T >
Stack< T >* Stack< T >::operator[](size_t id) const
{
  return stack_[id];
}

template< typename T >
Stack< T >* Stack< T >::at(size_t id) const
{
  if (id >= OVERFLOW)
  {
    throw std::out_of_range("Out of range");
  }
  return stack_[id];
}
