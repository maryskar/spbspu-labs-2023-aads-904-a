#ifndef NODE_H
#define NODE_H


template< class T >
class nodeList
{
  T data;
  nodeList< T >* next;
};
#endif
