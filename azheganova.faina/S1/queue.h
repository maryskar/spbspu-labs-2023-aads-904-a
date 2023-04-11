#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"

template< typename T >
class Queue
{
public:
  Queue();
  Queue(const Queue< T > & queue);
  ~Queue();
  void push(const T & rhs);
  T pop();
  bool isEmpty();
  T & drop();
private:
  ListNode< T > * top_;
  ListNode< T > * last_;
};

template< typename T >
Queue< T >::Queue():
 top_(nullptr),
 last_(nullptr)
{}

template < typename T >
Queue< T >::Queue(const Queue< T >& queue):
  top_(nullptr),
  last_(nullptr)
{
  ListNode< T > * tmp = queue.top_;
  while (tmp != nullptr)
  {
    push(tmp->data_);
    tmp = tmp->next_;
  }
}


template< typename T >
Queue< T >::~Queue()
{
  while (top_ != nullptr)
  {
    ListNode< T > * tmp = top_->next_;
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
    last_->next_ = new ListNode< T >{rhs, nullptr};
    last_ = last_->next_;
  }
  else
  {
    last_->next_ = new ListNode< T >{rhs, nullptr};
    last_ = last_->next_;
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

template< typename T >
T & Queue< T >::drop()
{
  if(isEmpty())
  {
    throw std::logic_error("empty queue");
  }
  return top_->data_;
}

#endif
