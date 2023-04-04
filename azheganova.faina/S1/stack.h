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
  int getSize();
private:
  ListNode< T > * top_;
  int size;
};

#endif