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
    Queue(Queue< T > && rhs);
    Queue< T > & operator=(const Queue< T > & rhs);
    Queue< T > & operator=(Queue< T > && rhs);
    void push(const T & rhs);
    void pop();
    bool isEmpty() const;
    T get() const;
    void clearQueue();
  private:
    details::ListNode< T > * top_;
    details::ListNode< T > * last_;
  };

  template< typename T >
  Queue< T >::Queue():
   top_(nullptr),
   last_(nullptr)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T > & rhs):
   top_(nullptr),
   last_(nullptr)
  {
    details::ListNode< T > * tmp = rhs.top_;
    while (tmp != nullptr)
    {
      try
      {
        push(tmp->data_);
      }
      catch (const std::exception & e)
      {
        clearQueue();
        throw;
      }
      tmp = tmp->next_;
    }
  }

  template< typename T >
  Queue< T >::Queue(Queue< T > && rhs):
   top_(rhs.top_),
   last_(rhs.last_)
   {
     top_ = nullptr;
     last_ = nullptr;
   }

  template< typename T>
  Queue< T > & Queue<T>::operator=(const Queue< T > & rhs)
  {
    if (this != std::addressof(rhs))
    {
      Queue< T > newqueue(rhs);
      *this = std::move(newqueue);
    }
    return *this;
  }

  template< typename T >
  Queue< T > & Queue< T >::operator=(Queue< T > && rhs)
  {
    if (this != std::addressof(rhs))
    {
      clearQueue();
      top_ = rhs.top_;
      last_ = rhs.last_;
      rhs.top_ = nullptr;
      rhs.last_ = nullptr;
    }
    return *this;
  }

  template< typename T >
  Queue< T >::~Queue()
  {
    clearQueue();
  }

  template < typename T >
  void Queue< T >::push(const T & rhs)
  {
    if (!isEmpty())
    {
      last_->next_ = new details::ListNode< T >{rhs, nullptr};
      last_ = last_->next_;
    }
    else
    {
      last_ = new details::ListNode< T >{rhs, nullptr};
      top_ = last_;
    }
  }

  template < typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("empty queue");
    }
    details::ListNode< T > * tmp = top_->next_;
    delete top_;
    top_ = tmp;
  }

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return top_ == nullptr;
  }

  template< typename T >
  T Queue< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("empty queue");
    }
    return top_->data_;
  }

  template < typename T >
  void Queue< T >::clearQueue()
  {
    while (!isEmpty())
    {
      pop();
    }
  }
}

#endif
