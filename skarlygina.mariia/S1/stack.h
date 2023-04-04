#ifndef STACK_H
#define STACK_H
#include "node.h"
template< typename T >
class Stack
{
public:
  Stack();
  void push(T rhs);
  T drop();
  ~Stack();
private:
  Node< T >* head;
};
#endif
