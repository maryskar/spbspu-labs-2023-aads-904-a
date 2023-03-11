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
   Queue():
     head(nullptr)
   {}
   Queue(const Queue< T >& q):
     head(nullptr)
   {
     details::NodeOfList< T >* copy = q.head;
     while (copy)
     {
       push(copy->data);
       copy = copy->next;
     }
   }
   Queue(Queue< T >&& q):
     head(q.head)
   {
     q.head = nullptr;
   }
   Queue< T >& operator=(const Queue< T >& q)
   {
     details::clear(&head);
     details::NodeOfList< T >* temp = q.head;
     while (temp)
     {
       push(temp->data);
       temp = temp->next;
     }
     return *this;
   }
   Queue< T >& operator=(Queue< T >&& q)
   {
     details::clear(&head);
     head = q.head;
     q.head = nullptr;
     return *this;
   }
   ~Queue()
   {
     details::clear(&head);
   }
   void push(T& rhs);
   T getHeadElem() const;
   void popFront();
   bool isEmpty() const;
  private:
   details::NodeOfList< T >* head;
  };

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
  T Queue< T >::getHeadElem() const
  {
    if (details::isEmpty(head))
    {
      throw std::underflow_error("Underflow!");
    }
    return details::getFront(head);
  }

  template< typename T >
  void Queue< T >::popFront()
  {
    if (details::isEmpty(head))
    {
      throw std::underflow_error("Underflow!");
    }
    details::popFront(&head);
  }
}
#endif
