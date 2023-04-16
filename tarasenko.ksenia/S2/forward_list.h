#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <memory>
#include <algorithm>
#include "node.h"
#include "forward_list_iterator.h"
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
     copy(other);
   }
   ForwardList(ForwardList< T >&& other):
     first(other.first)
   {
     other.first = nullptr;
   }
   ForwardList< T >& operator=(const ForwardList< T >& other)
   {
     try
     {
       details::clear(std::addressof(first));
       copy(other);
       return *this;
     }
     catch (...)
     {
       details::clear(std::addressof(first));
       throw;
     }
   }
   ForwardList< T >& operator=(ForwardList< T >&& other)
   {
     move(other);
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
   void copy(const ForwardList< T >& other);
   void move(const ForwardList< T >&& other);
   void insert(const T& data);
   void removeData(const T& data);

   friend class ForwardListIterator< T >;
   ForwardListIterator< T > begin()
   {
     return ForwardListIterator< T >(this);
   }

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
  void ForwardList< T >::insert(const T& data)
  {
    details::NodeOfList< T >** current = &first;
    while (*current && ((*current)->data) < data) //comparator
    {
      current = &(*current)->next;
    }
    *current = new details::NodeOfList< T >(data, *current);
  }

  template< typename T >
  void ForwardList< T >::removeData(const T& data)
  {
    details::NodeOfList< T >** current = &first;
    while (*current && (*current)->data < data) //comparator
    {
      current = &(*current)->next;
    }
    while (*current && data == (*current)->data)
    {
      details::NodeOfList< T >* to_delete = *current;
      *current = (*current)->next;
      details::popFront(&to_delete);
    }
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    details::clear(std::addressof(first));
  }

  template< typename T >
  void ForwardList< T >::copy(const ForwardList< T >& other)
  {
    details::NodeOfList< T >* copy = other.first;
    while (copy)
    {
      pushBack(copy->data);
      copy = copy->next;
    }
  }
  template< typename T >
  void ForwardList< T >::move(const ForwardList< T >&& other)
  {
    details::clear(std::addressof(first));
    first = other.first;
    other.first = nullptr;
  }
}
#endif
