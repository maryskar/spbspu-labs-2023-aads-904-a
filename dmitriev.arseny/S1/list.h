#ifndef LIST_H
#define LIST_H

template< typename T >
struct List
{
  T data;
  List< T >* next;

  List(T data = T(), List< T >* next = nullptr);
};

template< typename T >
inline List< T >::List(T data, List< T >* next):
  data(data),
  next(next)
{

}

#endif
