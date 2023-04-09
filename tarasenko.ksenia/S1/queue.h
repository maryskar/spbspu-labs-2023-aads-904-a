#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"
#include "forward_list.h"
namespace tarasenko
{
  template< typename T>
  class Queue
  {
  public:
   Queue()
   {}
   Queue(const Queue< T >& q)
   {
     head.copy(q.head);
   }
   Queue(Queue< T >&& q):
     head(q.head)
   {}
   Queue< T >& operator=(const Queue< T >& q)
   {
     try
     {
       head = q.top;
     }
     catch (...)
     {
       throw;
     }
     return *this;
   }
   Queue< T >& operator=(Queue< T >&& q)
   {
     head = q.top;
     q.top = nullptr;
     return *this;
   }
   ~Queue()
   {
     head.clear();
   }
   void push(T& rhs);
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
  void Queue< T >::push(T& rhs)
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
