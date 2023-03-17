#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "stack.h"
template < typename T >
class Queue
{
public:
  Queue();
  Queue(const Queue< std::string>& pQueue);
  ~Queue();
  void push(const T &rhs);
  T pop();
  bool isEmpty() const
  {
    return size_ == 0;
  }
private:
  details::ListNode< T > *head_;
  details::ListNode< T > *tail_;
  size_t size_;
};

template < typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
}

template < typename T >
Queue< T >::Queue(const Queue< std::string>& pQueue):
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
  details::ListNode< T > *tmp = pQueue.head_;
  while (tmp != nullptr)
  {
    push(tmp->data_);
    tmp = tmp->next_;
  }
}

template < typename T >
Queue< T >::~Queue()
{
  while (!isEmpty())
  {
    pop();
  }
}

template < typename T >
void Queue< T >::push(const T &rhs)
{
  if (head_ == nullptr)
  {
    head_ = new details::ListNode< T >{rhs, nullptr};
    tail_ = head_;
  }
  else
  {
    tail_->next_ = new details::ListNode< T >{rhs, nullptr};
    tail_ = tail_->next_;
  }
  size_++;
}

template < typename T >
T Queue< T >::pop()
{
  if (head_ == nullptr)
  {
    throw;
  }
  T el = head_->data_;
  details::ListNode< T > *subHead = head_->next_;
  delete head_;
  head_ = subHead;
  size_--;
  return el;
}
#endif
