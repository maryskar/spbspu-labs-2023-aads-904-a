#ifndef NODE_H
#define NODE_H

template< typename T >
struct Node
{
  T value;
  Node* p_next;

  Node(T value, Node* p_next = nullptr);
};

#endif
