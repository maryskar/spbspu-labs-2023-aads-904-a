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
  class ConstForwardListIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
  public:
   using this_t = ConstForwardListIterator< T >;

   ConstForwardListIterator():
     node(nullptr)
   {}
   explicit ConstForwardListIterator(const ForwardList< T >* list):
     node(list->first_)
   {}
   ConstForwardListIterator(const this_t&) = default;
   ~ConstForwardListIterator() = default;

   this_t& operator=(const this_t&) = default;

   this_t& operator++();
   this_t operator++(int);

   const T& operator*() const;
   const T* operator->() const;

   bool operator!=(const this_t&) const;
   bool operator==(const this_t&) const;

   const details::NodeOfList< T >* getNode() const
   {
     return node;
   }

  private:
   details::NodeOfList< T >* node;
  };

  template< typename T >
  ConstForwardListIterator< T >& ConstForwardListIterator< T >::operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }
  template< typename T >
  ConstForwardListIterator< T > ConstForwardListIterator< T >::operator++(int)
  {
    assert(node != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }
  template< typename T >
  const T& ConstForwardListIterator< T >::operator*() const
  {
    assert(node != nullptr);
    return node->data;
  }
  template< typename T >
  const T* ConstForwardListIterator< T >::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }
  template< typename T >
  bool ConstForwardListIterator< T >::operator==(const this_t& other) const
  {
    return node == other.node;
  }
  template< typename T >
  bool ConstForwardListIterator< T >::operator!=(const this_t& other) const
  {
    return !(node == other.node);
  }
}
#endif
