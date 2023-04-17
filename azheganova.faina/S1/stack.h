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
  T & drop() const;
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
  while (!isEmpty())
  {
    ListNode< T > * tmp = top_->next_;
    delete top_;
    top_ = tmp;
    size_--;
  }
}

template < typename T >
void Stack< T >::push(const T & rhs)
{
  if (top_ == nullptr)
  {
    top_ = new ListNode< T >{rhs, nullptr};
  }
  else
  {
    ListNode< T > * tmp = new ListNode< T >{rhs, top_};
    top_ = tmp;
  }
  size_++;
}

template< typename T >
void Stack< T >::pop()
{
  if (isEmpty())
  {
    throw std::logic_error("empty stack");
  }
  ListNode< T > * tmp = top_->next_;
  delete top_;
  top_ = tmp;
  size_--;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return size_ == 0;
}

template< typename T >
T & Stack< T >::drop() const
{
  if(isEmpty())
  {
    throw std::logic_error("empty stack");
  }
  return top_->data_;
}

#endif
