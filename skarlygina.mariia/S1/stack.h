#ifndef STACK_H
#define STACK_H
#include "list.h"
template< typename T >
class Stack
{
public:
  Stack();
  Stack(const Stack< T >& rhs);
  void push(T rhs);
  T drop();
  ~Stack();
private:
  List< T >* head_;
  List< T >* tail_;
};

template< typename T >
Stack< T >::Stack() :
  head_(nullptr),
  tail_(nullptr)
{}
#endif
