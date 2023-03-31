#ifndef NODE_H
#define NODE_H

template < typename T >
struct listNode
{
  T data_;
  Node< T > *next_;
};

#endif