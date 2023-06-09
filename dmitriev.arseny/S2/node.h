#ifndef NODE_H
#define NODE_H

#include <stdexcept>

template< typename T >
struct Node
{
  T data;
  Node< T >* next;
};

template< typename T >
void clear(Node< T >* head)
{
  while (head)
  {
    Node< T >* newHead = head->next;
    delete head;
    head = newHead;
  }
}

#endif
