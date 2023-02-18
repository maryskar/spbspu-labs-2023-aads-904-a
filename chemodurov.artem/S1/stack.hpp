#ifndef STACK_HPP
#define STACK_HPP

template< typename T >
class Stack
{
 public:
  void push(const T & rhs);
  void pop();
  T & getLast();
};
#endif
