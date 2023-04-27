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
   {}
   ForwardList(const ForwardList< T >& other):
     first(details::newCopy(other.first))
   {}
   ForwardList(ForwardList< T >&& other):
     first(other.first)
   {
     other.first = nullptr;
   }
   ForwardList< T >& operator=(const ForwardList< T >& other)
   {
     if (*this != other)
     {
       details::NodeOfList< T >* new_node = newCopy(other.first);
       details::clear(std::addressof(first));
       first = new_node;
     }
     return *this;
   }
   ForwardList< T >& operator=(ForwardList< T >&& other)
   {
     if (*this != other)
     {
       details::clear(std::addressof(first));
       first = other.first;
       other.first = nullptr;
     }
     return *this;
   }
   ~ForwardList()
   {
     details::clear(std::addressof(first));
   };
   bool isEmpty() const;
   void pushFront(const T& data);
   void pushBack(const T& data);
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
  void ForwardList< T >::pushFront(const T& data)
  {
    details::pushFront(std::addressof(first), data);
  }

  template< typename T >
  void ForwardList< T >::pushBack(const T& data)
  {
    details::pushBack(std::addressof(first), data);
  }

  template< typename T >
  T ForwardList< T >::getFront() const
  {
    return details::getFront(first);
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {
    details::popFront(std::addressof(first));
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    details::clear(std::addressof(first));
  }
}
#endif
