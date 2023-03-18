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
  bool isEmpty() const;
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
  if (!stack_)
  {
    stack_ = new list_t< T >{rhs, nullptr};
    top_ = stack_;
  }
  else
  {
    top_->next = new list_t< T >{rhs, nullptr};
    top_ = top_->next;
  }
}

template< typename T >
void Stack< T >::pop()
{
  if (!stack_)
  {
    throw std::underflow_error("Stack underflow");
  }
  else if (top_ == stack_)
  {
    delete top_;
    stack_ = nullptr;
    top_ = stack_;
  }
  else
  {
    list_t< T >* predTop = stack_;
    while (predTop->next != top_)
    {
      predTop = predTop->next;
    }
    delete top_;
    top_ = predTop;
    top_->next = nullptr;
  }
}

template< typename T >
T Stack< T >::drop()
{
  T var = top_->data;
  pop();
  return var;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return stack_;
}
#endif
