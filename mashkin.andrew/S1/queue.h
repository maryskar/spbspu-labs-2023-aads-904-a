#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "list.h"

namespace mashkin
{
  template< typename T >
  class Queue
  {
  public:
    explicit Queue();
    Queue(const Queue< T >& lhs);
    Queue(Queue< T >&& rhs);

    void enqueue(T rhs);
    void dequeue();
    bool isEmpty() const;
    T& drop();

  private:
    list_t< T >* head_;
    list_t< T >* tail_;
  };
}

template< typename T >
mashkin::Queue< T >::Queue():
  head_(nullptr),
  tail_(head_)
{
}

template< typename T >
void mashkin::Queue< T >::enqueue(T rhs)
{
  if (!head_)
  {
    head_ = new list_t< T >{rhs, nullptr};
    tail_ = head_;
  }
  else
  {
    tail_->next = new list_t< T >{rhs, nullptr};
    tail_ = tail_->next;
  }
}

template< typename T >
void mashkin::Queue< T >::dequeue()
{
  if (!head_)
  {
    throw std::underflow_error("Queue underflow");
  }
  else if (tail_ == head_)
  {
    delete tail_;
    head_ = nullptr;
    tail_ = head_;
  }
  else
  {
    list_t< T >* var = head_->next;
    delete head_;
    head_ = var;
  }
}

template< typename T >
T& mashkin::Queue< T >::drop()
{
  if (!head_)
  {
    throw std::underflow_error("Queue underflow");
  }
  return head_->data;
}

template< typename T >
bool mashkin::Queue< T >::isEmpty() const
{
  return head_;
}
#endif
