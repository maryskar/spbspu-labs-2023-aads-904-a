#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
#include "list.h"

template< typename T >
class Stack
{
public:
  explicit Stack();

  void push(T rhs);
  void pop();
  T drop();

private:
  list_t< T >* stack_;
  list_t< T >* top_;
};


template< typename T >
Stack< T >::Stack():
  stack_(nullptr),
  top_(stack_)
{
}

template< typename T >
void Stack< T >::push(T rhs)
{
  if (!top_->data)
  {
    top_ = new list_t< T >{rhs, nullptr};
  }
  top_->next = new list_t< T >{rhs, nullptr};
  top_ = top_->next;
}

template< typename T >
void Stack< T >::pop()
{
  if (!stack_->data)
  {
    throw std::underflow_error("Stack underflow");
  }
  delete top_;
  top_ = stack_->next;
  while (top_->next)
  {
    top_ = top_->next;
  }
}

template< typename T >
T Stack< T >::drop()
{
  T var = top_->data;
  pop();
  return var;
}
#endif
