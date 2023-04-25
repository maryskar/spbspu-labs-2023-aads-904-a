#ifndef STACK_H
#define STACK_H
#include "list.h"
template< typename T >
class Stack
{
 public:
  Stack();
  ~Stack();
  void push(const T &rhs);
  T &getOutOfStack();
  void pop();
 private:
  List< T > *head_;
};
#endif
