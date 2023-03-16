#include "queue.h"
#include <cstddef>
#include <stdexcept>

template< typename T >
Queue< T >::Queue():
  queue_{0},
  head_(0),
  tail_(0)
{
}

template< typename T >
void Queue< T >::enqueue(T rhs)
{
  if (tail_ == OVERFLOW)
  {
    throw std::overflow_error("Queue overflow");
  }
  queue_[tail_++];
}

template< typename T >
void Queue< T >::dequeue()
{
  if (tail_ + 1 == head_)
  {
    throw std::underflow_error("Queue underflow");
  }
  queue_[head_++];
}

template< typename T >
T Queue< T >::drop()
{
  dequeue();
  return queue_[head_ - 1];
}
