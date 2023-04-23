#ifndef LIST_HPP
#define LIST_HPP

template < typename T >
struct List
{
  T data;
  List< T >* next;
};

#endif

