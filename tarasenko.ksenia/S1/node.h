#ifndef NODE_H
#define NODE_H
namespace tarasenko
{
  template< typename T >
  struct Node
  {
    T value;
    Node* p_next;

    Node(T value, Node* p_next = nullptr);
  };

  template< typename T >
  Node< T >::Node(T value, Node* p_next):
   value(value),
   p_next(p_next)
  {}
}
#endif
