#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H

#include <memory>
#include <cassert>
#include <iterator>
#include <../S1/node.h>

namespace tarasenko
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ConstForwardListIterator;

  template< typename T >
  class ForwardListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
   using this_t = ForwardListIterator< T >;
   friend class ForwardList< T >;
   friend class ConstForwardListIterator< T >;

   ForwardListIterator():
     node_(nullptr)
   {}
   explicit ForwardListIterator(details::NodeOfList< T >* node):
     node_(node)
   {}
   ForwardListIterator(const this_t&) = default;
   ~ForwardListIterator() = default;

   this_t& operator=(const this_t&) = default;

   this_t& operator++();
   this_t operator++(int);

   T& operator*();
   T* operator->();

   T& operator*() const;
   T* operator->() const;

   bool operator!=(const this_t&) const;
   bool operator==(const this_t&) const;

  private:
   details::NodeOfList< T >* node_;
  };

  template< typename T >
  ForwardListIterator< T >& ForwardListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }
}
#endif
