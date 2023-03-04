#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "stack.h"
#include <iostream>
#include <algorithm>
template < typename T >
class Queue
{
public:
  Queue();
  Queue(const Queue< std::string>& pQueue);
/*Queue(const Queue< T >& input):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
  }*/
  ~Queue();
  void push(T rhs);
  T pop();
  bool isEmpty()
  {
    return size_ == 0;
  }
  void print()
  {
    Node< T > *e = head_;
    while (e != nullptr)
    {
      std::cout << e->data_;
      e = e->next_;
    }
    std::cout << "\n";
  }
private:
  Node< T > *head_;
  Node< T > *tail_;
  size_t size_;
};
template < typename T >
Queue< T >::Queue(const Queue< std::string>& pQueue):
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
  Node< T > *tmp = pQueue.head_;
  while (tmp != nullptr)
  {
    push(tmp->data_);
    tmp = tmp->next_;
  }
}
template < typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
}
template < typename T >
T Queue< T >::pop()
{
  T el = head_->data_;
  Node< T > *subHead = head_->next_;
  delete head_;
  head_ = subHead;
  size_--;
  return el;
}
template < typename T >
Queue< T >::~Queue()
{
}
template < typename T >
void Queue< T >::push(T rhs)
{
  if (head_ == nullptr)
  {
    head_ = new Node< T >{rhs, nullptr};
    tail_ = head_;
  }
  else
  {
    tail_->next_ = new Node< T >{rhs, nullptr};
    tail_ = tail_->next_;
  }
  size_++;
}
#endif
