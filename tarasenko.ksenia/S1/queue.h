#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

template< typename T>
class Queue
{
public:
 Queue();
 ~Queue();
 void push(T rhs);
 T drop();
private:
  Node< T >* head;
};

template< typename T >
Queue< T >::Queue():
 head(nullptr)
{}

template< typename T >
Queue< T >::~Queue()
{
  while (head)
  {
    drop();
  }
}

template< typename T >
void Queue< T >::push(T rhs)
{
  if (head == nullptr)
  {
    head = new Node< T >(rhs);
  }
  else
  {
    Node< T >* current = head;
    while (current->p_next != nullptr)
    {
      current = current->p_next;
    }
    current->p_next = new Node< T >(rhs);
  }
}

template< typename T >
T Queue< T >::drop()
{
  Node< T >* temp = head;
  head = head->p_next;
  T temp_val = temp->value;
  delete temp;
  return temp_val;
}

#endif
