#ifndef NODE_H
#define NODE_H


template< class T >
struct NodeList
{
  T data;
  NodeList< T >* next;
};
#endif
