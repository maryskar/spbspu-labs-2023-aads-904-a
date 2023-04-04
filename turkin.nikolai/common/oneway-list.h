#ifndef ONEWAY_LIST_H
#define ONEWAY_LIST_H

template< typename T >
struct OneWayList
{
  T data;
  OneWayList< T > * next;
};

#endif
