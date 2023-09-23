#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "iterator.h"
#include "citerator.h"
#include "list.h"

namespace skarlygina
{
  template < typename T >
  class ForwardList
  {
    ForwardList();
    ForwardList(const ForwardList< T >&);
    ForwardList(ForwardList< T >&&) noexcept;
    ~ForwardList();

    Iterator< T > begin();
    Iterator< T > end();
    CIterator< T > begin() const;
    CIterator< T > end() const;
    CIterator< T > cbegin() const;
    CIterator< T > cend() const;
  };

  template< typename T >
  ForwardList< T >::ForwardList():
    List< T >::List()
  {}

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T >& other):
    List< T >::List(other)
  {}

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T >&& other) noexcept:
    List< T >::List(other)
  {}

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    List< T >::~List();
  }

}

#endif

