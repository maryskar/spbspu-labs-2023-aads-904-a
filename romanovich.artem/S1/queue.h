#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
template < typename T >
class Queue
{
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T drop();
  void splitLine(const std::string &string);
  void parseQueue();
private:
  Node< T > *head_;
  Node< T > *tail_;
  size_t size_;
};
template < typename T >
T Queue< T >::drop()
{
  return nullptr;
}
template < typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
}
template < typename T >
Queue< T >::~Queue()
{
}
template < typename T >
void Queue< T >::splitLine(const std::string &string)
{
  for (char c: string)
  {
    if (c != ' ')
    {
      push(c);
    }
  }
}
template < typename T >
void Queue< T >::parseQueue()
{
  T nextEl = head_->data_;
  std::cout << "First: " << nextEl << "\n";
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
    tail_ = tail_->next_;
    tail_ = new Node< T >{rhs, nullptr};
    std::cout << rhs << " " << head_->data_ << " " << tail_->data_ << "\n";
  }
}
#endif
