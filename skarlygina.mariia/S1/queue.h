#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"
template< typename T >
class Queue
{
public:
  Queue();
  Queue(const Queue< T >& rhs);
  bool isEmpty() const;
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
bool Queue< T >::isEmpty() const
{
  return head_ == nullptr;
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
  if (head == nullptr)
  {
    throw std::out_of_range("Queue is empty");
  }
  Node< T >* newhead = head->next;
}
#endif
