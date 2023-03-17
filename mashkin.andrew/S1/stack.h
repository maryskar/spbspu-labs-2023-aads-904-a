#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include "list.h"

template< typename T >
class Stack
{
public:
  explicit Stack(T symb);

  void push(T rhs);
  void pop();
  T drop();

private:
  list_t< T > stack_;
  list_t< T > top_;
};
#endif
