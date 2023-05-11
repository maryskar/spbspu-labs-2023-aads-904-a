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
     first_(nullptr),
     size_(0)
   {
     null_->next = nullptr;
   }
   ForwardList(const ForwardList< T >& other):
     null_(static_cast< details::NodeOfList< T >* >(::operator new (sizeof(details::NodeOfList< T >)))),
     first_(details::newCopy(other.first_)),
     size_(other.size_)
   {
     null_->next = first_;
   }
   ForwardList(ForwardList< T >&& other):
     null_(other.null_),
     first_(other.first_),
     size_(other.size_)
   {
     other.null_ = nullptr;
     other.first_ = nullptr;
     other.size_ = 0;
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
       size_ = other.size_;
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
       size_ = other.size_;
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
   ForwardListIterator< T > insertAfter(ConstForwardListIterator< T > pos, const T& value);
   ForwardListIterator< T > insertBefore(ConstForwardListIterator< T > pos, const T& value);
   ForwardListIterator< T > eraseAfter(ConstForwardListIterator< T > pos);
   ForwardListIterator< T > eraseAfter(ConstForwardListIterator< T > first, ConstForwardListIterator< T > last);
   void resize(size_t count);
   void resize(size_t count, const T& value);
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
   size_t size_;
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
    size_++;
  }

  template< typename T >
  void ForwardList< T >::pushBack(const T& data)
  {
    details::pushBack(std::addressof(first_), data);
    size_++;
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
    size_--;
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::insertAfter(ConstForwardListIterator< T > pos, const T& value)
  {
    auto new_node = new details::NodeOfList< T >(value, pos.node_->next);
    pos.node_->next = new_node;
    size_++;
    return ForwardListIterator< T >(new_node);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::insertBefore(ConstForwardListIterator< T > pos, const T& value)
  {
    auto new_node = new details::NodeOfList< T >(value, nullptr);
    if (pos == cbegin())
    {
      new_node->next = first_;
      first_ = new_node;
      null_->next = first_;
    }
    else
    {
      auto prev = cbegin();
      auto curr = cbegin();
      while (curr != pos)
      {
        prev = curr;
        curr++;
      }
      new_node->next = prev.node_->next;
      prev.node_->next = new_node;
    }
    size_++;
    return ForwardListIterator< T >(new_node);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::eraseAfter(ConstForwardListIterator< T > pos)
  {
    auto to_delete = pos.node_->next;
    if (to_delete)
    {
      pos.node_->next = pos.node_->next->next;
    }
    delete to_delete;
    size_--;
    return ForwardListIterator< T >(pos.node_->next);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::eraseAfter(ConstForwardListIterator< T > first,
      ConstForwardListIterator< T > last)
  {
    auto pos = first;
    while (pos != last)
    {
      pos = eraseAfter(pos);
    }
    return ForwardListIterator< T >(last.node_);
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count)
  {
    if (count < size_)
    {

    }
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count, const T& value)
  {}

  template< typename T >
  void ForwardList< T >::removeNode(details::NodeOfList< T >* pnode) //...
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
