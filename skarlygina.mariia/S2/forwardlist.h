#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "iterator.h"
#include "citerator.h"

namespace skarlygina
{
  template < typename T >
  class ForwardList
  {
    ForwardList();
    ForwardList(const ForwardList< T >&);
    ForwardList(ForwardList< T >&&);
    ~ForwardList();

    Iterator< T > begin();
    Iterator< T > end();
    CIterator< T > begin() const;
    CIterator< T > end() const;
    CIterator< T > cbegin() const;
    CIterator< T > cend() const;
  };
}

#endif

