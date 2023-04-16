#ifndef NODE_H
#define NODE_H


template< class T >
struct nodeList
{
  T data;
  nodeList< T >* next;
};
#endif
