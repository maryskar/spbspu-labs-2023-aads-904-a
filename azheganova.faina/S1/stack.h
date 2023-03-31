#ifndef STACK_H
#define STACK_H
#include "node.h"

template< typename T >
class Stack
{
public:
  Stack();
  ~Stack();
  void push(const T & rhs);
  void pop();
  bool isEmpty();
  T drop();
private:
  ListNode< T > * top_;
};

#endif