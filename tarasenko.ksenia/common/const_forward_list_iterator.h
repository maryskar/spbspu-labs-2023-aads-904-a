#ifndef CONST_FORWARD_LIST_ITERATOR_H
#define CONST_FORWARD_LIST_ITERATOR_H

#include <memory>
#include <cassert>
#include <iterator>
#include "node.h"

namespace tarasenko
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ForwardListIterator;

  template< typename T >
  class ConstForwardListIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
  public:
   using this_t = ConstForwardListIterator< T >;
   friend class ForwardList< T >;
   friend class ForwardListIterator< T >;

   ConstForwardListIterator():
     node_(nullptr)
   {}
   explicit ConstForwardListIterator(details::NodeOfList< T >* node):
     node_(node)
   {}
   ConstForwardListIterator(const ForwardListIterator< T >& iter):
     node_(iter.node_)
   {}
   ConstForwardListIterator(const this_t&) = default;
   ~ConstForwardListIterator() = default;

   this_t& operator=(const this_t&) = default;
   this_t& operator=(const ForwardListIterator< T >& other);

   this_t& operator++();
   this_t operator++(int);

   const T& operator*() const;
   const T* operator->() const;

   bool operator!=(const this_t&) const;
   bool operator==(const this_t&) const;

  private:
   details::NodeOfList< T >* node_;
  };

  template< typename T >
  ConstForwardListIterator< T >& ConstForwardListIterator< T >::operator=(const ForwardListIterator< T >& other)
  {
    node_ = other.node_;
    return *this;
  }

  template< typename T >
  ConstForwardListIterator< T >& ConstForwardListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ConstForwardListIterator< T > ConstForwardListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T& ConstForwardListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T* ConstForwardListIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ConstForwardListIterator< T >::operator==(const this_t& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ConstForwardListIterator< T >::operator!=(const this_t& other) const
  {
    return !(node_ == other.node_);
  }
}
#endif
