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
    Queue(Queue< T > &&pQueue) noexcept;
    ~Queue();
    Queue< T > &operator=(const Queue< T > &pQueue);
    Queue< T > &operator=(Queue< T > &&pQueue);
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
    void deleteQueue();
    void doSwap(Queue< T > &q) noexcept;
  };
  template < typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > &&pQueue)
  {
    if (this != &pQueue)
    {
      deleteQueue();
      doSwap(pQueue);
    }
    return *this;
  }
  template < typename T >
  Queue< T > &Queue< T >::operator=(const Queue< T > &pQueue)
  {
    doSwap(pQueue);
    return *this;
  }
  template < typename T >
  void Queue< T >::deleteQueue()
  {
    details::clear(head_);
    head_ = nullptr;
    tail_ = nullptr;
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
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    details::ListNode< T > *tmp = pQueue.head_;
    while (tmp != nullptr)
    {
      try
      {
        push(tmp->data_);
      }
      catch (...)
      {
        Queue< T >::deleteQueue();
        throw;
      }
      tmp = tmp->next_;
    }
  }
  template < typename T >
  Queue< T >::Queue(Queue< T > &&pQueue) noexcept:
    head_(pQueue.head_),
    tail_(pQueue.tail_),
    size_(pQueue.size_)
  {
    pQueue.head_ = nullptr;
    pQueue.tail_ = nullptr;
    pQueue.size_ = 0;
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
    Queue< T >::deleteQueue();
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
