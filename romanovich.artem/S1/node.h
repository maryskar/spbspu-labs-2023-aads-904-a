#ifndef NODE_H
#define NODE_H
#include <stdexcept>
template < typename T >
struct Node
{
  T data_;
  Node< T > *next_;
};
#endif