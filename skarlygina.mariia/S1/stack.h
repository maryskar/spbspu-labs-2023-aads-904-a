#ifndef STACK_H
#define STACK_H
#include "list.h"
template< typename T >
class Stack
{
public:
  Stack();
  Stack(const Stack& rhs);
  void push(T rhs);
  T drop();
  ~Stack();
private:
  List< T >* head;
  List< T >* tail;
};
#endif
