#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"
namespace tarasenko
{
  template< typename T>
  class Queue
  {
  public:
   Queue();
   Queue(const Queue< T >& q);
   ~Queue();
   void push(T& rhs);
   T drop();
   bool isEmpty() const;
  private:
   details::NodeOfList< T >* head;
  };

  template< typename T >
  Queue< T >::Queue():
    head(nullptr)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T >& q):
    head(nullptr)
  {
    details::NodeOfList< T >* copy = q.head;
    while (copy)
    {
      push(copy->data);
      copy = copy->next;
    }
  }

  template< typename T >
  Queue< T >::~Queue()
  {
    while (head)
    {
      details::popFront(&head);
    }
  }

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return details::isEmpty(head);
  }

  template< typename T >
  void Queue< T >::push(T& rhs)
  {
    details::pushBack(&head, rhs);
  }

  template< typename T >
  T Queue< T >::drop()
  {
    if (details::isEmpty(head))
    {
      throw std::underflow_error("Underflow!");
    }
    return details::dropFront(&head);
  }
}
#endif
