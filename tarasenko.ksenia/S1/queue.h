#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"

template< typename T>
class Queue
{
public:
 Queue();
 ~Queue();
 void push(T rhs);
 T drop();
 bool isEmpty();
private:
  Node< T >* head;
  size_t size;
};

template< typename T >
Queue< T >::Queue():
 head(nullptr),
 size(0)
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
bool Queue< T >::isEmpty()
{
  return size == 0;
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
  size++;
}

template< typename T >
T Queue< T >::drop()
{
  if (!size)
  {
    throw std::underflow_error("Underflow!\n");
  }
  Node< T >* temp = head;
  head = head->p_next;
  T temp_val = temp->value;
  delete temp;
  size--;
  return temp_val;
}

#endif
