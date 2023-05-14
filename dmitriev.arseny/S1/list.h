#ifndef LIST_H
#define LIST_H

#include <stdexcept>

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
  std::pair< List< T >*, List< T >* > copy(List< T >* otherHead)
  {
    if (otherHead == nullptr)
    {
      return std::pair< List< T >*, List< T >* >{nullptr, nullptr};
    }
    List< T >* newHead = new dmitriev::List< T >{otherHead->data};
    List< T >* newTail = newHead;
    otherHead = otherHead->otherList;

    while (otherHead != nullptr)
    {
      try
      {
        newTail->otherList = new dmitriev::List< T >{otherHead->data};
      }
      catch (const std::exception&)
      {
        clear(newHead);
        throw;
      }

      newTail = newTail->otherList;
      otherHead = otherHead->otherList;
    }

    return std::pair< List< T >*, List< T >* >{newHead, newTail};
  }
}

#endif
