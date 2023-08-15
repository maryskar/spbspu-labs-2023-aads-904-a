#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H
#include <iterator>
#include "node.h"

namespace kryuchkova
{
  template < typename T >
  class ForwardList;

  template < typename T >
  class ForwardListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    public:
      using this_t = ForwardIterator< T >;
  }
}

#endif
