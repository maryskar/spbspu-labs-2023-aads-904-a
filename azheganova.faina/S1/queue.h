#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"

namespace azheganova
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    ~Queue();
    Queue(const Queue< T > & rhs);
    Queue(const Queue< T > && rhs);
    void push(const T & rhs);
    void pop();
    bool isEmpty();
    T & drop();
  private:
    details::ListNode< T > * top_;
    details::ListNode< T > * last_;
    size_t size_;
  };

  template< typename T >
  Queue< T >::Queue():
   top_(nullptr),
   last_(nullptr),
   size_(0)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T > & rhs):
   top_(nullptr),
   last_(nullptr),
   size_(0)
  {
    details::ListNode< T > * tmp = rhs.top_;
    while (tmp != nullptr)
    {
      push(tmp->data_);
      tmp = tmp->next_;
    }
  }

  template< typename T >
  Queue< T >::Queue(const Queue< T > && rhs):
   top_(rhs.top_),
   last_(rhs.last_),
   size_(rhs.size_)
   {
     top_ = nullptr;
     last_ = nullptr;
     size_ = 0;
   }

  template< typename T >
  Queue< T >::~Queue()
  {
    while (top_ != nullptr)
    {
      pop();
    }
  }

  template < typename T >
  void Queue< T >::push(const T & rhs)
  {
    if (top_ == nullptr)
    {
      top_ = new details::ListNode< T >{rhs, nullptr};
      last_ = top_;
    }
    else
    {
      last_->next_ = new details::ListNode< T >{rhs, nullptr};
      last_ = last_->next_;
    }
    size_++;
  }

  template < typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw;
    }
    details::ListNode< T > * tmp = top_->next_;
    delete top_;
    top_ = tmp;
    size_--;
  }

  template< typename T >
  bool Queue< T >::isEmpty()
  {
    return size_ == 0;
  }

  template< typename T >
  T & Queue< T >::drop()
  {
    if(isEmpty())
    {
      throw std::logic_error("empty queue");
    }
    return top_->data_;
  }
}

#endif
