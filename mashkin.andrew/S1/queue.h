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
    Queue();
    Queue(const Queue< T >& lhs);
    Queue(Queue< T >&& rhs) noexcept;
    ~Queue();

    void enqueue(const T& rhs);
    void dequeue();
    bool isEmpty() const noexcept;
    T& getHead() const;

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
mashkin::Queue< T >::Queue(const Queue< T >& lhs):
  head_(nullptr),
  tail_(nullptr)
{
  auto var = head_;
  while (var)
  {
    enqueue(var->data);
    var = var->next;
  }
}

template< typename T >
mashkin::Queue< T >::Queue(Queue< T >&& rhs) noexcept:
  head_(rhs.head_),
  tail_(rhs.tail_)
{
  rhs.head_ = nullptr;
  rhs.tail_ = nullptr;
}

template< typename T >
mashkin::Queue< T >::~Queue()
{
  while(isEmpty())
  {
    this->dequeue();
  }
}

template< typename T >
void mashkin::Queue< T >::enqueue(const T& rhs)
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
T& mashkin::Queue< T >::getHead() const
{
  if (!head_)
  {
    throw std::underflow_error("Queue underflow");
  }
  return head_->data;
}

template< typename T >
bool mashkin::Queue< T >::isEmpty() const noexcept
{
  return head_;
}
#endif
