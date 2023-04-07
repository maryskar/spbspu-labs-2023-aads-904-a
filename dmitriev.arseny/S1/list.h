#ifndef LIST_H
#define LIST_H

template< typename T >
struct List
{
  T data;
  List< T >* otherList;

  List(T data = T(), List< T >* otherList = nullptr);
};

template< typename T >
List< T >::List(T data, List< T >* otherList) :
  data(data),
  otherList(otherList)
{

}

#endif
