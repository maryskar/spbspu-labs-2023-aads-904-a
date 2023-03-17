#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "list.h"

template< typename T >
class Queue
{
public:
  explicit Queue();
  void enqueue(T rhs);
  void dequeue();
  T drop();

private:
  list_t< T >* head_;
  list_t< T >* tail_;
};

template< typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(head_)
{
}

template< typename T >
void Queue< T >::enqueue(T rhs)
{
  if (!tail_->data)
  {
    tail_ = new list_t< T >{rhs, nullptr};
  }
  tail_->next = new list_t< T >{rhs, nullptr};
  tail_ = tail_->next;
}

template< typename T >
void Queue< T >::dequeue()
{
  if (tail_ == head_)
  {
    throw std::underflow_error("Queue underflow");
  }
  list_t< T > var = head_->next;
  delete head_;
  head_ = var;
}

template< typename T >
T Queue< T >::drop()
{
  T var = head_->data;
  dequeue();
  return var;
}
#endif
