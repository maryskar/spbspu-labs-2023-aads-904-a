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
    T * value_;
    size_t size_;
    size_t capacity_;
  };
}

template< typename T >
chemodurov::Stack< T >::Stack():
 value_(new T[1]),
 size_(0),
 capacity_(1)
{}

template< typename T >
chemodurov::Stack< T >::~Stack()
{
  delete [] value_;
}

#endif
