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
   void push(T rhs);
   T drop();
   bool isEmpty() const;
  private:
   details::NodeOfList< T >* head;
   size_t size;
  };

  template< typename T >
  Queue< T >::Queue():
    head(nullptr),
    size(0)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T >& q):
    head(nullptr),
    size(q.size)
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
  void Queue< T >::push(T rhs)
  {
    details::pushBack(&head, rhs);
    size++;
  }

  template< typename T >
  T Queue< T >::drop()
  {
    if (size == 0)
    {
      throw std::underflow_error("Underflow!");
    }
    size--;
    return details::dropFront(&head);
  }
}
#endif
