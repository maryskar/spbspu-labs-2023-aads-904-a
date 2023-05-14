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

  template< typename T >
  List< T >* copy(List< T >*& newHead, List< T >* otherHead)
  {
    if (otherHead == nullptr)
    {
      return nullptr;
    }
    newHead = new dmitriev::List< T >{otherHead->data};
    List< T >* newTail = newHead;
    otherHead = otherHead->otherList;

    while (otherHead != nullptr)
    {
      newTail = newTail->otherList;
      try
      {
        newTail = new dmitriev::List< T >{otherHead->data};
      }
      catch (const std::exception&)
      {
        clear(newHead);
        throw;
      }

      otherHead = otherHead->otherList;
    }

    return newTail;
  }
}

#endif
