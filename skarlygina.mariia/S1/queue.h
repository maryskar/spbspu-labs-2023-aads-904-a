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
  Queue(const Queue< T >& other);
  void push(const T& rhs);
  T& get() const;
  void pop();
  bool isEmpty() const;
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
Queue< T >::Queue(const Queue< T >& other):
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
void Queue< T >::push(const T& rhs)
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
void Queue< T >::pop()
{
  if (head_ == nullptr)
  {
    throw std::out_of_range("Queue is empty");
  }
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
}

template< typename T >
T& Queue< T >::get() const
{
  if (head_ == nullptr)
  {
    throw std::out_of_range("Queue is empty");
  }
  return head_->data;
}

template< typename T >
bool Queue< T >::isEmpty() const
{
  return head_.isEmpty();
}

template< typename T >
Queue< T >::~Queue()
{
  while (head_ != nullptr)
  {
    pop();
  }
}
#endif
