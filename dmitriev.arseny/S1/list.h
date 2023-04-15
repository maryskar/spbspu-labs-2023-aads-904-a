#ifndef LIST_H
#define LIST_H

template< typename T >
struct List
{
  T data;
  List< T >* otherList;

  List(const T& data, List< T >* otherList = nullptr);
};

template< typename T >
List< T >::List(const T& data, List< T >* otherList):
  data(data),
  otherList(otherList)
{

}

template< typename T >
void clear(List< T >* topAdress)
{
  while (topAdress != nullptr)
  {
    List< T >* currentList = topAdress;
    topAdress = topAdress->otherList;

    delete currentList;
  }
}

#endif
