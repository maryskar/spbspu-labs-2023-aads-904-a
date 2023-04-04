#ifndef ONEWAY_LIST_H
#define ONEWAY_LIST_H

template< typename T >
struct OneWayNode
{
  T data;
  OneWayList< T > * next;
};

#endif
