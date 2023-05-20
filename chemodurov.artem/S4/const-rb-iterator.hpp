#ifndef S4_CONST_RB_ITERATOR_HPP
#define S4_CONST_RB_ITERATOR_HPP
#include "const-bidirectional-iterator.hpp"
#include "rb-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class ConstRBIterator
  {
    using this_t = ConstRBIterator< T, Compare >;
    ConstRBIterator();
    ConstRBIterator(const RBIterator< T, Compare > & rhs);
    ConstRBIterator(const this_t &) = default;
    ~ConstRBIterator() = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
   private:
    ConstBidirectionalIterator< std::pair< T, char >, Compare > iter;
  };

  template< typename T, typename Compare >
  ConstRBIterator< T, Compare >::ConstRBIterator():
   iter()
  {}

  template< typename T, typename Compare >
  ConstRBIterator< T, Compare >::ConstRBIterator(const RBIterator< T, Compare > & rhs):
   iter(rhs.iter)
  {}

  template< typename T, typename Compare >
  ConstRBIterator< T, Compare > & ConstRBIterator< T, Compare >::operator++()
  {
    return ++iter;
  }

  template< typename T, typename Compare >
  ConstRBIterator< T, Compare > ConstRBIterator< T, Compare >::operator++(int)
  {
    return iter++;
  }

  template< typename T, typename Compare >
  ConstRBIterator< T, Compare > & ConstRBIterator< T, Compare >::operator--()
  {
    return --iter;
  }

  template< typename T, typename Compare >
  ConstRBIterator< T, Compare > ConstRBIterator< T, Compare >::operator--(int)
  {
    return iter--;
  }

  template< typename T, typename Compare >
  const T & ConstRBIterator< T, Compare >::operator*() const
  {
    return (*iter).first;
  }

  template< typename T, typename Compare >
  const T * ConstRBIterator< T, Compare >::operator->() const
  {
    return std::addressof((*iter).first);
  }
}

#endif
