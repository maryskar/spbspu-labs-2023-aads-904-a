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
      friend class ForwardList< T >;

      ForwardListIterator():
        node_(nullptr)
      {}
      explicit ForwardIterator(Node< T > * node):
        node_(node)
      {}
      ForwardIterator(const this_t&) = default;
      ~ForwardIterator() = default;

      ForwardIterator& operator++();
      ForwardIterator operator++(int);
      bool operator!=(const this_t&) const;
      bool operator==(const this_t&) const;

    private:
      Node< T > * node_;
  };
}

#endif
