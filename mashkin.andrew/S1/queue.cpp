#include "queue.h"
#include <cstddef>
#include <stdexcept>

template< typename T >
Queue< T >::Queue(T symb):
  head_(new list_t< T >{symb, nullptr}),
  tail_(head_)
{
}

template< typename T >
void Queue< T >::enqueue(T rhs)
{
  tail_.next = new list_t< T >{rhs, nullptr};
  tail_ = tail_.next;
}

template< typename T >
void Queue< T >::dequeue()
{
  if (tail_ == head_)
  {
    throw std::underflow_error("Queue underflow");
  }
  list_t< T > var = head_.next;
  delete head_;
  head_ = var;
}

template< typename T >
T Queue< T >::drop()
{
  T var = head_.data;
  dequeue();
  return var;
}
