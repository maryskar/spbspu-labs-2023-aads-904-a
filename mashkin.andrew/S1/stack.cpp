#include "stack.h"
#include <cstddef>
#include <stdexcept>

template< typename T >
Stack< T >::Stack(T symb):
  stack_(new list_t< T >{symb, nullptr}),
  top_(stack_)
{
}

template< typename T >
void Stack< T >::push(T rhs)
{
  top_.next = new list_t< T >{rhs, nullptr};
  top_ = top_.next;
}

template< typename T >
void Stack< T >::pop()
{
  if (!stack_.data)
  {
    throw std::underflow_error("Stack underflow");
  }
  delete top_;
  top_ = stack_.next;
  while (top_.next)
  {
    top_ = top_.next;
  }
}

template< typename T >
T Stack< T >::drop()
{
  T var = top_.data;
  pop();
  return var;
}
