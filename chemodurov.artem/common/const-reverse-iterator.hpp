#ifndef S4_CONST_REVERSE_ITERATOR_HPP
#define S4_CONST_REVERSE_ITERATOR_HPP
#include "const-bidirectional-iterator.hpp"
#include "reverse_iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare = std::less< > >
  class ConstReverseIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template< typename, typename, typename >
    friend class Map;
   public:
    using this_t = ConstReverseIterator< T, Compare >;
    ConstReverseIterator();
    ConstReverseIterator(const ReverseIterator< T, Compare > & rhs);
    ConstReverseIterator(const this_t &) = default;
    ~ConstReverseIterator() = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
   private:
    ConstBidirectionalIterator< T, Compare > iter_;
    explicit ConstReverseIterator(ConstBidirectionalIterator< T, Compare > iter);
  };

  template< typename T, typename Compare >
  ConstReverseIterator< T, Compare >::ConstReverseIterator():
    iter_()
  {}

  template< typename T, typename Compare >
  ConstReverseIterator< T, Compare >::ConstReverseIterator(const ReverseIterator< T, Compare > & rhs):
    iter_(rhs.iter_)
  {}

  template< typename T, typename Compare >
  ConstReverseIterator< T, Compare > & ConstReverseIterator< T, Compare >::operator++()
  {
    --iter_;
    return *this;
  }

  template< typename T, typename Compare >
  ConstReverseIterator< T, Compare > ConstReverseIterator< T, Compare >::operator++(int)
  {
    return this_t(iter_--);
  }

  template< typename T, typename Compare >
  ConstReverseIterator< T, Compare > & ConstReverseIterator< T, Compare >::operator--()
  {
    ++iter_;
    return *this;
  }

  template< typename T, typename Compare >
  ConstReverseIterator< T, Compare > ConstReverseIterator< T, Compare >::operator--(int)
  {
    return this_t(iter_++);
  }

  template< typename T, typename Compare >
  const T & ConstReverseIterator< T, Compare >::operator*() const
  {
    return iter_.operator*();
  }

  template< typename T, typename Compare >
  const T * ConstReverseIterator< T, Compare >::operator->() const
  {
    return iter_.operator->();
  }
}

#endif
