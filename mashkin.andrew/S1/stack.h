#ifndef STACK_H
#define STACK_H

template< typename T >
class Stack
{
public:
  void push(T rhs);
  void pop();
  T drop();
};
#endif
