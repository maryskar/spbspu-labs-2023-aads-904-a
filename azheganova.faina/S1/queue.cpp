#include "queue.h"


template< typename T >
Queue< T >::Queue():
 top_(nullptr),
 last_(nullptr)
{}

template< typename T >
Queue< T >::~Queue()
{
  while (top_ != nullptr)
  {
    ListNode< T > * tmp = top_->next;
    delete top_;
    top_ = tmp;
  }
}

template< typename T >
void Queue< T >::push(const T & rhs)
{
  if (!last_)
  {
    last_ = new ListNode< T >{rhs, nullptr};
    top_ = last_;
    last_->next = new ListNode< T >{rhs, nullptr};
    last_ = last_->next;
  }
  else
  {
    last_->next = new ListNode< T >{rhs, nullptr};
    last_ = last_->next;
  }
}

template < typename T >
T Queue< T >::pop()
{
  if (isEmpty())
  {
    throw;
  }
  T value = top_->data_;
  ListNode< T > * newhead = top_->next_;
  delete top_;
  top_ = newhead;
  return value;
}

template< typename T >
bool Queue< T >::isEmpty()
{
  return top_ == nullptr;
}
