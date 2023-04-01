#ifndef LIST_HPP
#define LIST_HPP

template < typename T >
struct List
{
  T data_;
  List< T > *next_;
};

#endif