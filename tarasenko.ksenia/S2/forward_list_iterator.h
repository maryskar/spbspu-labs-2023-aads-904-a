#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H

#include "forward_list.h"
#include <memory>

namespace tarasenko
{
  template< typename T >
  class ForwardListIterator
  {
  public:
   using this_t = ForwardListIterator< T >;

   ForwardListIterator() :
     node(nullptr)
   {}
   ForwardListIterator(const this_t&) = default;
   ~ForwardListIterator() = default;

   this_t& operator=(const this_t&) = default;

   this_t& operator++();
   this_t operator++(int);

   T& operator*(); //+ const-версия
   T* operator->(); //+ const-версия

   bool operator!=(const this_t&) const;

   bool operator==(const this_t&) const;

  private:
   ForwardList< T >* node;
  };

  template< typename T >
  ForwardListIterator< T >::this_t& ForwardListIterator< T >::operator++()
  {
    assert(node != nullptr);
    node = node->next;
  }

  template< typename T >
  ForwardListIterator< T >::this_t ForwardListIterator< T >::operator++(int)
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

}
#endif
