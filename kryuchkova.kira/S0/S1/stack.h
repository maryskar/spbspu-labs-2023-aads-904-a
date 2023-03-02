#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"

namespace gelaz
{
  template < typename T >
  class Stack
  {
    public:
      Stack()
      ~Stack()
      void push(T rhs)
      T drop()
      bool isEmpty()
    private:
      Node< T > *head_;
  };
}
#endif
