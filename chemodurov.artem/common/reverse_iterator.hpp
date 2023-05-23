#ifndef S4_REVERSE_ITERATOR_HPP
#define S4_REVERSE_ITERATOR_HPP
#include "bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class ConstReverseIterator;

  template< typename T, typename Compare = std::less< > >
  class ReverseIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template< typename, typename, typename >
    friend class Map;
    friend class ConstReverseIterator< T, Compare >;
   public:
    using this_t = ReverseIterator< T, Compare >;
    ReverseIterator();
    ReverseIterator(const this_t &) = default;
    ~ReverseIterator() = default;
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
    BidirectionalIterator< T, Compare > iter_;
    explicit ReverseIterator(BidirectionalIterator< T, Compare > iter);
  };

  template< typename T, typename Compare >
  ReverseIterator< T, Compare >::ReverseIterator():
    iter_()
  {}

  template< typename T, typename Compare >
  ReverseIterator< T, Compare > & ReverseIterator< T, Compare >::operator++()
  {
    --iter_;
    return *this;
  }

  template< typename T, typename Compare >
  ReverseIterator< T, Compare > ReverseIterator< T, Compare >::operator++(int)
  {
    return this_t(iter_--);
  }

  template< typename T, typename Compare >
  ReverseIterator< T, Compare > & ReverseIterator< T, Compare >::operator--()
  {
    ++iter_;
    return *this;
  }

  template< typename T, typename Compare >
  ReverseIterator< T, Compare > ReverseIterator< T, Compare >::operator--(int)
  {
    return this_t(iter_++);
  }

  template< typename T, typename Compare >
  const T & ReverseIterator< T, Compare >::operator*() const
  {
    return (static_cast< const ConstBidirectionalIterator< T, Compare > >(iter_)).operator*();
  }

  template< typename T, typename Compare >
  const T * ReverseIterator< T, Compare >::operator->() const
  {
    return (static_cast< const ConstBidirectionalIterator< T, Compare > >(iter_)).operator->();
  }

  template< typename T, typename Compare >
  T & ReverseIterator< T, Compare >::operator*()
  {
    return iter_.operator*();
  }

  template< typename T, typename Compare >
  T * ReverseIterator< T, Compare >::operator->()
  {
    return iter_.operator->();
  }
}

#endif
