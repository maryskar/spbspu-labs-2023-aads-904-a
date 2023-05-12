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
   using iterator = ForwardListIterator< T >;
   using const_iterator = ConstForwardListIterator< T >;
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
   iterator insertAfter(const_iterator pos, const T& value);
   iterator insertBefore(const_iterator pos, const T& value);
   iterator eraseAfter(const_iterator pos);
   iterator eraseAfter(const_iterator first, const_iterator last);
   void resize(size_t count);
   void resize(size_t count, const T& value);
   void swap(ForwardList< T >& other);
   void removeNode(details::NodeOfList< T >* pnode);

   friend class ForwardListIterator< T >;
   iterator beforeBegin() const
   {
     return iterator(null_);
   }
   iterator begin() const
   {
     return iterator(first_);
   }
   iterator end() const
   {
     return iterator();
   }

   friend class ConstForwardListIterator< T >;
   const_iterator cbeforeBegin() const
   {
     return const_iterator(null_);
   }
   const_iterator cbegin() const
   {
     return const_iterator(first_);
   }
   const_iterator cend() const
   {
     return const_iterator();
   }

  private:
   details::NodeOfList< T >* null_;
   details::NodeOfList< T >* first_;
   size_t size_;
  };

  template< typename T >
  bool ForwardList< T >::isEmpty() const
  {
    return size_ == 0;
  }

  template< typename T >
  void ForwardList< T >::pushFront(const T& data)
  {
    insertAfter(cbeforeBegin());
  }

  template< typename T >
  void ForwardList< T >::pushBack(const T& data)
  {
    if (first_ == nullptr)
    {
      first_ = new details::NodeOfList< T >(data, nullptr);
      null_->next = first_;
    }
    else
    {
      details::NodeOfList< T >* current = first_;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = new details::NodeOfList< T >(data, nullptr);
    }
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
    eraseAfter(cbeforeBegin());
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::insertAfter(const_iterator pos, const T& value)
  {
    auto new_node = new details::NodeOfList< T >(value, pos.node_->next);
    pos.node_->next = new_node;
    if (pos.node_ == null_)
    {
      first_ = new_node;
    }
    size_++;
    return iterator(new_node);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::insertBefore(const_iterator pos, const T& value)
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
  ForwardListIterator< T > ForwardList< T >::eraseAfter(const_iterator pos)
  {
    auto to_delete = pos.node_->next;
    if (to_delete)
    {
      pos.node_->next = pos.node_->next->next;
    }
    if (pos.node_ == null_)
    {
      first_ = pos.node_->next;
      null_->next = first_;
    }
    delete to_delete;
    size_--;
    return iterator(pos.node_->next);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::eraseAfter(const_iterator first, const_iterator last)
  {
    auto pos = first;
    while (first != last)
    {
      first = eraseAfter(pos);
    }
    return iterator(last.node_);
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count)
  {
    if (count == size_)
    {
      return;
    }
    auto curr = cbegin();
    for (size_t i = 1; i < size_ && i < count; i++)
    {
      curr++;
    }
    if (count < size_)
    {
      eraseAfter(curr, cend());
    }
    else if (count > size_)
    {
      while (size_ < count)
      {
        pushBack(T());
      }
    }
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count, const T& value)
  {
    if (count == size_)
    {
      return;
    }
    auto curr = cbegin();
    for (size_t i = 1; i < size_ && i < count; i++)
    {
      curr++;
    }
    if (count < size_)
    {
      eraseAfter(curr, cend());
    }
    else if (count > size_)
    {
      while (size_ < count)
      {
        pushBack(value);
      }
    }
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T >& other)
  {
    std::swap(null_, other.null_);
    std::swap(first_, other.first_);
    std::swap(size_, other.size_);
  }

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
    first_ = nullptr;
    size_ = 0;
  }
}
#endif
