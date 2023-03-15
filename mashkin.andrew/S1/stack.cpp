#include "stack.h"
#include <cstddef>

template< typename T >
Stack< T >::Stack():
  stack_(0),
  top_{0}
{}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return top_;
}
