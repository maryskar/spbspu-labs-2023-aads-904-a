#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <memory>
#include <algorithm>
#include "node.h"
#include "forward_list_iterator.h"
#include "const_forward_list_iterator.h"

namespace tarasenko
{
  template< typename T >
  class ForwardList
  {
  public:
   ForwardList():
     first_(nullptr)
   {}
   ForwardList(const ForwardList< T >& other):
     first_(details::newCopy(other.first_))
   {}
   ForwardList(ForwardList< T >&& other):
     first_(other.first_)
   {
     other.first_ = nullptr;
   }
   ForwardList< T >& operator=(const ForwardList< T >& other)
   {
     if (this != std::addressof(other))
     {
       details::NodeOfList< T >* new_node = newCopy(other.first_);
       details::clear(std::addressof(first_));
       first_ = new_node;
     }
     return *this;
   }
   ForwardList< T >& operator=(ForwardList< T >&& other)
   {
     if (this != std::addressof(other))
     {
       details::clear(std::addressof(first_));
       first_ = other.first_;
       other.first_ = nullptr;
     }
     return *this;
   }
   ~ForwardList()
   {
     details::clear(std::addressof(first_));
   }
   bool isEmpty() const;
   void pushFront(const T& data);
   void pushBack(const T& data);
   T getFront() const;
   void popFront();
   void clear();
   void copy(const ForwardList< T >& other);
   void addBefore(details::NodeOfList< T >* pnode, const T& data);
   void removeNode(details::NodeOfList< T >* pnode);
   void removeData(const T& data);

   friend class ForwardListIterator< T >;
   ForwardListIterator< T > begin()
   {
     return ForwardListIterator< T >(this);
   }
   ForwardListIterator< T > end()
   {
     return ForwardListIterator< T >();
   }

   friend class ConstForwardListIterator< T >;
   ConstForwardListIterator< T > cbegin() const
   {
     return ConstForwardListIterator< T >(this);
   }
   ConstForwardListIterator< T > cend() const
   {
     return ConstForwardListIterator< T >();
   }
  private:
   details::NodeOfList< T >* first_;
  };

  template< typename T >
  bool ForwardList< T >::isEmpty() const
  {
    return details::isEmpty(first_);
  }

  template< typename T >
  void ForwardList< T >::pushFront(const T& data)
  {
    details::pushFront(std::addressof(first_), data);
  }

  template< typename T >
  void ForwardList< T >::pushBack(const T& data)
  {
    details::pushBack(std::addressof(first_), data);
  }

  template< typename T >
  T ForwardList< T >::getFront() const
  {
    return details::getFront(first_);
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {
    details::popFront(std::addressof(first_));
  }

  template< typename T >
  void ForwardList< T >::addBefore(details::NodeOfList< T >* pnode, const T& data)
  {
    if (first_ == pnode)
    {
      auto new_node = new details::NodeOfList< T >(data, nullptr);
      new_node->next = first_;
      first_ = new_node;
    }
    else
    {
      details::NodeOfList< T >* prev = first_;
      details::NodeOfList< T >* curr = first_;
      while (curr != pnode)
      {
        prev = curr;
        curr = curr->next;
      }
      auto new_node = new details::NodeOfList< T >(data, nullptr);
      new_node->next = prev->next;
      prev->next = new_node;
    }
  }

  template< typename T >
  void ForwardList< T >::removeNode(details::NodeOfList< T >* pnode)
  {
    if (pnode == first_)
    {
      details::popFront(std::addressof(first_));
    }
    else
    {
      details::NodeOfList< T >* curr = first_;
      while (curr->next != pnode)
      {
        curr = curr->next;
      }
      curr->next = pnode->next;
      details::popFront(std::addressof(pnode));
    }
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    details::clear(std::addressof(first_));
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
}
#endif
