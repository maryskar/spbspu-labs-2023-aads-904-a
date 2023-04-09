#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <memory>
#include <algorithm>
#include "node.h"
namespace tarasenko
{
  template< typename T >
  class ForwardList
  {
  public:
   ForwardList():
     first(nullptr)
   {};

   ForwardList(const ForwardList< T >& other):
     first(nullptr)
   {

   }
   ForwardList(ForwardList< T >&& other):
     first(other.first)
   {
     other.first = nullptr;
   }
   ForwardList< T >& operator=(const ForwardList< T >& q)
   {

   }
   ForwardList< T >& operator=(ForwardList< T >&& q)
   {

   }
   ~ForwardList()
   {
     details::clear(std::addressof(first));
   };
   bool isEmpty() const;
   void pushFront(T& data);
   void pushBack(T& data);
   T getFront() const;
   void popFront();
   void clear();
  private:
   details::NodeOfList< T >* first;
  };

  template< typename T >
  bool ForwardList< T >::isEmpty() const
  {
    return details::isEmpty(first);
  }

  template< typename T >
  void ForwardList< T >::pushFront(T& data)
  {
    details::pushFront(&first, data);
  }

  template< typename T >
  void ForwardList< T >::pushBack(T& data)
  {
    details::pushBack(&first, data);
  }

  template< typename T >
  T ForwardList< T >::getFront() const
  {
    return details::getFront(first);
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {
    details::popFront(&first);
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    details::clear(&first);
  }
}
#endif
