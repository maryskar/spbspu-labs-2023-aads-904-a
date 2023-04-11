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
  T pop();
  bool isEmpty();
  T & drop();
private:
  ListNode< T > * top_;
  size_t size_;
};

template< typename T >
Stack< T >::Stack():
  top_(nullptr),
  size_(0)
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
  tmp->next_ = top_;
  top_ = tmp;
  size_++;
}

template< typename T >
T Stack< T >::pop()
{
  if (isEmpty())
  {
    throw;
  }
  T value = top_->data_;
  ListNode< T > * tmp = top_;
  top_ = top_->next_;
  delete tmp;
  size_--;
  return value;
}

template< typename T >
bool Stack< T >::isEmpty()
{
  return top_;
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
