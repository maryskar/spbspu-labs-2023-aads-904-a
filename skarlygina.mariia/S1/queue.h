#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "list.h"
template< typename T >
class Queue
{
public:
  Queue();
  Queue(const Queue< T >& rhs);
  void push(T rhs);
  T drop();
  ~Queue();
private:
  List< T >* head_;
  List< T >* tail_;
};

template< typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
Queue< T >::Queue(const Queue& other):
    head_(nullptr),
    tail_(nullptr)
{
  if (other.head_ == nullptr)
  {
    return;
  }
  List< T >* other_temp = other.head_;
  while (other_temp != nullptr)
  {
    push(other->data);
    other_temp = other_temp->next;
  }
}

template< typename T >
void Queue< T >::push(T rhs)
{
  List< T >* new_node = new List< T >{rhs, nullptr, tail_};
  if (tail_ != nullptr)
  {
    tail_->next = new_node;
  }
  tail_ = new_node;
  if (head_ == nullptr)
  {
    head_ = tail_;
  }
}

template< typename T >
T Queue< T >::drop()
{
  if (head_ == nullptr)
  {
    throw std::out_of_range("Queue is empty");
  }
  T data = head_->data;
  List< T >* head_temp = head_;
  head_ = head_->next;
  if (head_ != nullptr)
  {
    head_->prev = nullptr;
  }
  else
  {
    tail_ = nullptr;
  }
  delete head_temp;
  return data;
}
#endif
