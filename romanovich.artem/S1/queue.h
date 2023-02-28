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
  T pop();
  void splitLine(const std::string &string);
  void parseQueue();
private:
  Node< T > *head_;
  Node< T > *tail_;
  size_t size_;
};
template < typename T >
T Queue< T >::pop()
{
  T el = head_->data_;
  Node< T > *subHead = head_->next_;
  delete head_;
  head_ = subHead;
  return el;
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
  while (head_->next_ != nullptr)
  {
    std::cout << pop() << "-";
  }
  std::cout << pop();
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
}
#endif
