#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"
namespace romanovich
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue< T > &queue);
    Queue(Queue< T > &&queue) noexcept;
    ~Queue();
    Queue< T > &operator=(Queue< T > queue);
    Queue< T > &operator=(Queue< T > &&queue) noexcept;
    void push(const T &rhs);
    void pop();
    T get() const;
    bool isEmpty() const;
  private:
    details::ListNode< T > *head_;
    details::ListNode< T > *tail_;
    void deleteQueue();
    void swapQueue(Queue< T > &queue) noexcept;
  };
  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return head_ == nullptr;
  }
  template< typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > &&queue) noexcept
  {
    if (this != std::addressof(queue))
    {
      deleteQueue();
      swapQueue(queue);
    }
    return *this;
  }
  template< typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > queue)
  {
    swapQueue(queue);
    return *this;
  }
  template< typename T >
  void Queue< T >::deleteQueue()
  {
    details::clear(head_);
    head_ = nullptr;
    tail_ = nullptr;
  }
  template< typename T >
  Queue< T >::Queue():
    head_(nullptr),
    tail_(nullptr)
  {
  }
  template< typename T >
  Queue< T >::Queue(const Queue< T > &queue):
    Queue(details::copy(queue.head_))
  {
  }
  template< typename T >
  Queue< T >::Queue(Queue< T > &&queue) noexcept:
    head_(queue.head_),
    tail_(queue.tail_)
  {
    queue.head_ = nullptr;
    queue.tail_ = nullptr;
  }
  template< typename T >
  void Queue< T >::swapQueue(Queue< T > &queue) noexcept
  {
    std::swap(head_, queue.head_);
    std::swap(tail_, queue.tail_);
  }
  template< typename T >
  Queue< T >::~Queue()
  {
    Queue< T >::deleteQueue();
  }
  template< typename T >
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
  }
  template< typename T >
  T Queue< T >::get() const
  {
    if (isEmpty())
    {
      throw std::range_error("Queue is empty.");
    }
    return head_->data_;
  }
  template< typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::range_error("Queue is empty.");
    }
    details::ListNode< T > *subHead = head_->next_;
    delete head_;
    head_ = subHead;
  }
}
#endif
