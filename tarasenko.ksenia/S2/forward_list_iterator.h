#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H
#include <memory>
#include <cassert>
#include "forward_list.h"

namespace tarasenko
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardListIterator
  {
  public:
   using this_t = ForwardListIterator< T >;

   ForwardListIterator() :
     node(nullptr)
   {}
   explicit ForwardListIterator(ForwardList< T >* list):
     node(list->first)
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
   details::NodeOfList< T >* node;
  };

  template< typename T >
  ForwardListIterator< T >& ForwardListIterator< T >::operator++()
  {
    assert(node != nullptr);
    node = node->next;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    assert(node != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator==(const this_t& rhs) const
  {
    return node == rhs.node;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*()
  {
    assert(node != nullptr);
    return node->data;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->()
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*() const
  {
    assert(node != nullptr);
    return node->data;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

}
#endif
