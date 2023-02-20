#ifndef STACK_HPP
#define STACK_HPP
#include <cstddef>

namespace chemodurov
{
  template< typename T >
  class Stack
  {
   public:
    Stack();
    ~Stack();
    void push(const T & rhs);
    void pop();
    T & getLast();
   private:
    T * value;
    size_t size;
    size_t capacity;
  };
}

#endif
