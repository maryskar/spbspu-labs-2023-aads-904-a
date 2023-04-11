#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
#include "node.h"

template< typename T >
class Stack
{
public:
  Stack();
  ~Stack();
  void push(const T & rhs);
  void pop();
  bool isEmpty() const;
  T & drop();
private:
  ListNode< T > * top_;
};

template< typename T >
Stack< T >::Stack():
  top_(nullptr)
{}

template< typename T >
Stack< T >::~Stack()
{
  while (top_ != nullptr)
  {
    ListNode< T > * tmp = top_->next_;
    delete top_;
    top_ = tmp;
  }
}

template< typename T >
void Stack< T >::push(const T & rhs)
{
  ListNode< T > * tmp = new ListNode< T >{rhs, top_};
  top_ = tmp;
}

template< typename T >
void Stack< T >::pop()
{
  if (isEmpty())
  {
    throw;
  }
  ListNode< T > * tmp = top_->next_;
  delete top_;
  top_ = tmp;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return top_ == nullptr;
}

template< typename T >
T & Stack< T >::drop()
{
  if(isEmpty())
  {
    throw std::logic_error("empty stack");
  }
  return top_->data_;
}


#endif
