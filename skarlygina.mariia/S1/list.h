#ifndef LIST_H
#define LIST_H
template< typename T >
struct List
{
  T data;
  List< T >* next;
  List< T >* prev;
};
#endif
