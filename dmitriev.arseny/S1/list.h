#ifndef LIST_H
#define LIST_H

namespace dmitriev
{
  template< typename T >
  struct List
  {
    T data;
    List< T >* otherList;
  };

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
}

#endif
