#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <utility>
#include <memory>
#include "node.h"
#include "forward_list.h"
namespace tarasenko
{
  template< typename T>
  class Queue
  {
  public:
   Queue():
     head_()
   {}
   Queue(const Queue< T >& q):
     head_(q.head_)
   {}
   Queue(Queue< T >&& q):
     head_(std::move(q.head_))
   {}
   Queue< T >& operator=(const Queue< T >& other)
   {
     if (this != std::addressof(other))
     {
       head_ = other.head_;
     }
     return *this;
   }
   Queue< T >& operator=(Queue< T >&& other)
   {
     if (this != std::addressof(other))
     {
       head_ = std::move(other.head_);
     }
     return *this;
   }
   ~Queue()
   {
     head_.clear();
   }
   void push(const T& rhs);
   T getHeadElem() const;
   void popFront();
   bool isEmpty() const;
  private:
   ForwardList< T > head_;
  };

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return head_.isEmpty();
  }

  template< typename T >
  void Queue< T >::push(const T& rhs)
  {
    head_.pushBack(rhs);
  }

  template< typename T >
  T Queue< T >::getHeadElem() const
  {
    if (head_.isEmpty())
    {
      throw std::logic_error("It's empty!");
    }
    return head_.getFront();
  }

  template< typename T >
  void Queue< T >::popFront()
  {
    if (head_.isEmpty())
    {
      throw std::logic_error("It's empty!");
    }
    head_.popFront();
  }
}
#endif
