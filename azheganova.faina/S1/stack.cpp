#include "stack.h"

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
    ListNode< T > * tmp = top_->next;
    delete top_;
    top_ = tmp;
  }
}

template< typename T >
void Stack< T >::push(const T & rhs)
{
  ListNode< T > * tmp = new ListNode< T >{rhs, top_};
  tmp->next = top_;
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
int Stack< T >::getSize()
{
  return size_;
}

template< typename T >
T Stack< T >::drop()
{
  return top_->data_;
}
