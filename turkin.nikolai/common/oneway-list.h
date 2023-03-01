#ifndef ONEWAY_LIST
#define ONEWAY_LIST

template< typename T >
struct OneWayList
{
  T data;
  OneWayList< T > * next;
};

#endif
