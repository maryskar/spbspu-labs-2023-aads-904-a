#ifndef S4_RB_ITERATOR_HPP
#define S4_RB_ITERATOR_HPP
#include "bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class RBIterator
  {
   public:
    using this_t = RBIterator< T, Compare >;
    RBIterator();
    RBIterator(const this_t &) = default;
    ~RBIterator() = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
   private:
    BidirectionalIterator< std::pair< T, char >, Compare > iter;
    RBIterator(BidirectionalIterator< std::pair< T, char >, Compare > it);
  };

  template< typename T, typename Compare >
  RBIterator< T, Compare >::RBIterator(BidirectionalIterator< std::pair< T, char >, Compare > it):
   iter(it)
  {}

  template< typename T, typename Compare >
  RBIterator< T, Compare > & RBIterator< T, Compare >::operator++()
  {
    return ++iter;
  }

  template< typename T, typename Compare >
  RBIterator< T, Compare > RBIterator< T, Compare >::operator++(int)
  {
    return iter++;
  }

  template< typename T, typename Compare >
  RBIterator< T, Compare > & RBIterator< T, Compare >::operator--()
  {
    return --iter;
  }

  template< typename T, typename Compare >
  RBIterator< T, Compare > RBIterator< T, Compare >::operator--(int)
  {
    return iter--;
  }

  template< typename T, typename Compare >
  T & RBIterator< T, Compare >::operator*()
  {
    return const_cast< T & >(*(static_cast< const this_t >(*this)));
  }

  template< typename T, typename Compare >
  const T & RBIterator< T, Compare >::operator*() const
  {
    return (*iter).first;
  }

  template< typename T, typename Compare >
  T * RBIterator< T, Compare >::operator->()
  {
    return const_cast< T & >((static_cast< const this_t >(*this)).operator->());
  }

  template< typename T, typename Compare >
  const T * RBIterator< T, Compare >::operator->() const
  {
    return std::addressof((iter.operator->())->first);
  }
}

#endif
