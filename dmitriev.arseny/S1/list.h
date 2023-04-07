#ifndef LIST_H
#define LIST_H

template< typename T >
struct List
{
  T data;
  List< T >* other;

  List(T data = T(), List< T >* other = nullptr);
};

template< typename T >
List< T >::List(T data, List< T >* other):
  data(data),
  other(other)
{

}

#endif
