#include "stack.h"

template< typename T >
Stack< T >::Stack():
  top_(nullptr)
{}

template< typename T >
Stack< T >::~Stack()
{
  while (top_ != nullptr)
  {
    ListNode< T > * temp = top_->next;
    delete top_;
    top_ = tmp;
  }
}

template< typename T >
void Stack< T >::push(const T & rhs)
{
  ListNode< T > * temp = new ListNode< T >{rhs, top_};
  top_ = tmp;
}

template< typename T >
void Stack< T >::pop()
{
  if (!top_)
  {
    throw std::logic_error("error");
  }
  ListNode< T > * tmp = top_->next;
  delete top_;
  top_ = tmp;
}

template< typename T >
bool Stack< T >::isEmpty()
{
  return top_;
}
