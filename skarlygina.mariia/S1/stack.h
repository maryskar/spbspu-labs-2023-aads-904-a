#ifndef STACK_H
#define STACK_H
#include "list.h"
template< typename T >
class Stack
{
public:
  Stack();
  Stack(const Stack< T >& other);
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

template< typename T >
Stack< T >::Stack(const Stack< T >& other):
  head_(nullptr),
  tail_(nullptr)
{
  if (other.head_ == nullptr)
  {
    return;
  }
  List< T >* head_temp = other.head_;
  while (head_temp != nullptr)
  {
    push(head_temp->data);
    head_temp = head_temp->next;
  }
}
#endif
