#ifndef S4_CONST_BIDIRECTIONAL_ITERATOR_HPP
#define S4_CONST_BIDIRECTIONAL_ITERATOR_HPP
#include "tree.hpp"

namespace chemodurov
{
  template< typename T >
  class ConstBidirectionalIterator
  {
   public:
    using this_t = ConstBidirectionalIterator< T >;
    ConstBidirectionalIterator();
    ConstBidirectionalIterator(const this_t &) = default;
    ~ConstBidirectionalIterator() = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
   private:
    Tree< T > * node_;
    Tree< T > * fake_;
  };

  template< typename T >
  ConstBidirectionalIterator< T >::ConstBidirectionalIterator():
   node_(nullptr),
   fake_(nullptr)
  {}
}
#endif
