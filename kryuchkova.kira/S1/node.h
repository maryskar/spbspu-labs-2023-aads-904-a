#ifndef NODE_H
#define NODE_H

namespace kryuchkova
{
  template< typename T >
  struct Node
  {
    T data_;
    Node *next_;
    Node(T rhs):
      data_(rhs),
      next_(nullptr)
    {}
  };
}

#endif
