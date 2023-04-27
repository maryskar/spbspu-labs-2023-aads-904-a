#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <utility>
#include "node.h"
#include "forward_list.h"
namespace tarasenko
{
  template< typename T>
  class Queue
  {
  public:
   Queue():
     head()
   {}
   Queue(const Queue< T >& q):
     head(q.head)
   {}
   Queue(Queue< T >&& q):
     head(std::move(q.head))
   {}
   Queue< T >& operator=(const Queue< T >& other)
   {
     if (*this != other)
     {
       head = other.top;
     }
     return *this;
   }
   Queue< T >& operator=(Queue< T >&& other)
   {
     if (*this != other)
     {
       head = std::move(other.head);
     }
     return *this;
   }
   ~Queue()
   {
     head.clear();
   }
   void push(const T& rhs);
   T getHeadElem() const;
   void popFront();
   bool isEmpty() const;
  private:
   ForwardList< T > head;
  };

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return head.isEmpty();
  }

  template< typename T >
  void Queue< T >::push(const T& rhs)
  {
    head.pushBack(rhs);
  }

  template< typename T >
  T Queue< T >::getHeadElem() const
  {
    if (head.isEmpty())
    {
      throw std::underflow_error("Underflow!");
    }
    return head.getFront();
  }

  template< typename T >
  void Queue< T >::popFront()
  {
    if (head.isEmpty())
    {
      throw std::underflow_error("Underflow!");
    }
    head.popFront();
  }
}
#endif
