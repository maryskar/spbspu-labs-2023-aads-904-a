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
     null_(static_cast< details::NodeOfList< T >* >(::operator new (sizeof(details::NodeOfList< T >)))),
     first_(nullptr)
   {
     null_->next = nullptr;
   }
   ForwardList(const ForwardList< T >& other):
     null_(static_cast< details::NodeOfList< T >* >(::operator new (sizeof(details::NodeOfList< T >)))),
     first_(details::newCopy(other.first_))
   {
     null_->next = first_;
   }
   ForwardList(ForwardList< T >&& other):
     null_(other.null_),
     first_(other.first_)
   {
     other.null_ = nullptr;
     other.first_ = nullptr;
   }
   ~ForwardList()
   {
     clear();
     ::operator delete(null_);
   }
   ForwardList< T >& operator=(const ForwardList< T >& other)
   {
     if (this != std::addressof(other))
     {
       details::NodeOfList< T >* new_node = newCopy(other.first_);
       details::clear(std::addressof(first_));
       first_ = new_node;
       null_->next = first_;
     }
     return *this;
   }
   ForwardList< T >& operator=(ForwardList< T >&& other)
   {
     if (this != std::addressof(other))
     {
       details::clear(std::addressof(first_));
       first_ = other.first_;
       null_->next = first_;
       other.first_ = nullptr;
     }
     return *this;
   }

   bool isEmpty() const;
   void pushFront(const T& data);
   void pushBack(const T& data);
   T& getFront();
   const T& getFront() const;
   void popFront();
   void clear();
   void addBefore(details::NodeOfList< T >* pnode, const T& data);
   void removeNode(details::NodeOfList< T >* pnode);

   friend class ForwardListIterator< T >;
   ForwardListIterator< T > beforeBegin() const
   {
     return ForwardListIterator< T >(null_);
   }
   ForwardListIterator< T > begin() const
   {
     return ForwardListIterator< T >(first_);
   }
   ForwardListIterator< T > end() const
   {
     return ForwardListIterator< T >();
   }

   friend class ConstForwardListIterator< T >;
   ConstForwardListIterator< T > cbeforeBegin() const
   {
     return ConstForwardListIterator< T >(null_);
   }
   ConstForwardListIterator< T > cbegin() const
   {
     return ConstForwardListIterator< T >(first_);
   }
   ConstForwardListIterator< T > cend() const
   {
     return ConstForwardListIterator< T >();
   }

  private:
   details::NodeOfList< T >* null_;
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
    null_->next = first_;
  }

  template< typename T >
  void ForwardList< T >::pushBack(const T& data)
  {
    details::pushBack(std::addressof(first_), data);
  }

  template< typename T >
  T& ForwardList< T >::getFront()
  {
    return details::getFront(first_);
  }

  template< typename T >
  const T& ForwardList< T >::getFront() const
  {
    return details::getFront(first_);
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {
    details::popFront(std::addressof(first_));
    null_->next = first_;
  }

  template< typename T >
  void ForwardList< T >::addBefore(details::NodeOfList< T >* pnode, const T& data)
  {
    if (first_ == pnode)
    {
      pushFront(data);
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
      popFront();
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
}
#endif
