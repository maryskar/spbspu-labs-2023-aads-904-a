#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "stack.h"
namespace romanovich
{
  template < typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue< T > &pQueue);
    Queue(const Queue< T > &&pQueue) noexcept;
    ~Queue();
    void push(const T &rhs);
    void pop();
    T get() const;
    bool isEmpty() const
    {
      return size_ == 0;
    }
  private:
    details::ListNode< T > *head_;
    details::ListNode< T > *tail_;
    size_t size_;
    void doSwap(Queue< T > &q) noexcept;
  };
  template < typename T >
  Queue< T >::Queue(const Queue< T > &&pQueue) noexcept:
    Queue()
  {
    doSwap(pQueue);
  }
  template < typename T >
  Queue< T >::Queue():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
  }
  template < typename T >
  Queue< T >::Queue(const Queue< T > &pQueue):
    Queue()
  {
    Queue tmp(pQueue);
    doSwap(tmp);
  }
  template < typename T >
  void Queue< T >::doSwap(Queue< T > &q) noexcept
  {
    std::swap(head_, q.head_);
    std::swap(tail_, q.tail_);
    std::swap(size_, q.size_);
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
  T Queue< T >::get() const
  {
    if (isEmpty())
    {
      throw std::range_error("Queue is empty.");
    }
    return head_->data_;
  }
  template < typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::range_error("Queue is empty.");
    }
    details::ListNode< T > *subHead = head_->next_;
    delete head_;
    head_ = subHead;
    size_--;
  }
}
#endif
