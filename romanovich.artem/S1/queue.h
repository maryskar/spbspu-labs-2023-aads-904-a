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
    Queue(const Queue< T > &queue);
    Queue(Queue< T > &&queue) noexcept;
    ~Queue();
    Queue< T > &operator=(Queue< T > queue);
    Queue< T > &operator=(Queue< T > &&queue) noexcept;
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
    void swapQueue(Queue< T > &queue) noexcept;
  };
  template < typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > &&queue) noexcept
  {
    if (this != &queue)
    {
      deleteQueue();
      swapQueue(queue);
    }
    return *this;
  }
  template < typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > queue)
  {
    swapQueue(queue);
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
  Queue< T >::Queue(const Queue< T > &queue)
  {
    if (queue.head_ == nullptr)
    {
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    }
    else
    {
      using list_node_tuple = std::tuple < details::ListNode< T > *, details::ListNode< T > * >;
      list_node_tuple *newQueue = details::copy(queue.head_);
      head_ = std::get<0>(newQueue);
      tail_ = std::get<1>(newQueue);
    }
  }
  template < typename T >
  Queue< T >::Queue(Queue< T > &&queue) noexcept:
    head_(queue.head_),
    tail_(queue.tail_),
    size_(queue.size_)
  {
    queue.head_ = nullptr;
    queue.tail_ = nullptr;
    queue.size_ = 0;
  }
  template < typename T >
  void Queue< T >::swapQueue(Queue< T > &queue) noexcept
  {
    std::swap(head_, queue.head_);
    std::swap(tail_, queue.tail_);
    std::swap(size_, queue.size_);
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
