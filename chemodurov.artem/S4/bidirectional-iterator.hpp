#ifndef S4_BIDIRECTIONAL_ITERATOR_HPP
#define S4_BIDIRECTIONAL_ITERATOR_HPP
#include <cassert>
#include "tree.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class ConstBidirectionalIterator;

  template< typename T, typename Compare >
  class UnbalancedBinarySearchTree;

  template< typename T, typename Compare >
  class RBTree;

  template< typename T, typename Compare = std::less< > >
  class BidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class UnbalancedBinarySearchTree< T, Compare >;
    friend class ConstBidirectionalIterator< T, Compare >;
    friend class RBTree< T, Compare >;
   public:
    using this_t = BidirectionalIterator< T, Compare >;
    BidirectionalIterator();
    BidirectionalIterator(const this_t &) = default;
    ~BidirectionalIterator() = default;
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
    Tree< T, Compare > * node_;
    Tree< T, Compare > * fake_;
    BidirectionalIterator(Tree< T, Compare > * node, Tree< T, Compare > * fake);
  };

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare >::BidirectionalIterator():
   node_(nullptr),
   fake_(nullptr)
  {}

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > & BidirectionalIterator< T, Compare >::operator++()
  {
    ConstBidirectionalIterator< T, Compare > temp(*this);
    ++temp;
    this->node_ = temp.node_;
    this->fake_ = temp.fake_;
    return *this;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BidirectionalIterator< T, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > & BidirectionalIterator< T, Compare >::operator--()
  {
    ConstBidirectionalIterator< T, Compare > temp(*this);
    --temp;
    this->node_ = temp.node_;
    this->fake_ = temp.fake_;
    return *this;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BidirectionalIterator< T, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    --(*this);
    return temp;
  }

  template< typename T, typename Compare >
  const T & BidirectionalIterator< T, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T, typename Compare >
  T & BidirectionalIterator< T, Compare >::operator*()
  {
    return const_cast< T & >((static_cast< const this_t >(*this)).operator*());
  }

  template< typename T, typename Compare >
  const T * BidirectionalIterator< T, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T, typename Compare >
  T * BidirectionalIterator< T, Compare >::operator->()
  {
    return const_cast< T * >((static_cast< const this_t >(*this)).operator->());
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare >::BidirectionalIterator(Tree< T, Compare > * node, Tree< T, Compare > * fake):
   node_(node),
   fake_(fake)
  {}

  template< typename T, typename Compare >
  bool operator==(const BidirectionalIterator< T, Compare > & lhs, const BidirectionalIterator< T, Compare > & rhs)
  {
    return lhs.operator->() == rhs.operator->();
  }

  template< typename T, typename Compare >
  bool operator!=(const BidirectionalIterator< T, Compare > & lhs, const BidirectionalIterator< T, Compare > & rhs)
  {
    return !(lhs == rhs);
  }
}
#endif
