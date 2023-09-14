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
  Queue(Queue< T >& other);
  Queue(Queue< T >&& other);
  void push(const T& rhs);
  const T& top() const;
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
Queue< T >::Queue(Queue< T >& other):
    head_(other.head_),
    tail_(other.tail_)
{}

template< typename T >
Queue< T >::Queue(Queue< T >&& other) :
  head_(other.head_),
  tail_(other.tail_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template< typename T >
void Queue< T >::push(const T& rhs)
{
  List< T >* new_node = new List< T >{rhs, nullptr};
  if (isEmpty())
  {
    tail_ = head_ = new_node;
  }
  else
  {
    tail_->next = new_node;
    tail_ = tail_->next;
  }
}

template< typename T >
void Queue< T >::pop()
{
  if (isEmpty())
  {
    throw std::out_of_range("Queue is empty");
  }
  List< T >* head_temp = head_;
  head_ = head_->next;
  if (head_ == tail_)
  {
    head_ = tail_ = nullptr;
  }
  else
  {
    head_ = head_->next;
  }
  delete head_temp;
}

template <class T>
const T& Queue< T >::top() const
{
  if (isEmpty()) {
    throw std::runtime_error("Queue is empty");
  }
  return head_->data;
}

template< typename T >
bool Queue< T >::isEmpty() const
{
  return tail_ == nullptr;
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
