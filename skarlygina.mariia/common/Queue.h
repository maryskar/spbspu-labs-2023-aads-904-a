#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "List.h"
namespace skarlygina
{
  template < typename T >
  class Queue
  {
  public:
    bool isEmpty() const;
    T front() const;
    T back() const;
    void pop();
    void push(const T&);
    void clear();
    void swap(Queue&) noexcept;
  private:
    detail::List< T > list_;
  };
  template < typename T >
  bool Queue< T >::isEmpty() const
  {
    return list_.isEmpty();
  }
  template < typename T >
  T Queue< T >::front() const
  {
    if (isEmpty())
    {
      throw std::logic_error("The queue is empty");
    }
    return list_.front();
  }
  template < typename T >
  T Queue< T >::back() const
  {
    if (isEmpty())
    {
      throw std::logic_error("The queue is empty");
    }
    return list_.back();
  }
  template < typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Pop from empty queue");
    }
    list_.popFront();
  }
  template < typename T >
  void Queue< T >::push(const T& data)
  {
    list_.pushBack(data);
  }
  template < typename T >
  void Queue< T >::clear()
  {
    list_.clear();
  }
  template < typename T >
  void Queue< T >::swap(Queue& other) noexcept
  {
    list_.swap(other.list_);
  }
}

#endif



