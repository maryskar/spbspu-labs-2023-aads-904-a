#ifndef STACK_H
#define STACK_H

template< typename T >
class Stack 
{
public:
  Stack();
  ~Stack();
  void push(T rhs);
  T drop;
  bool isEmpty();
};

#endif
