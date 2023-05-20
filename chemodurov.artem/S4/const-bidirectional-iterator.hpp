#ifndef S4_CONST_BIDIRECTIONAL_ITERATOR_HPP
#define S4_CONST_BIDIRECTIONAL_ITERATOR_HPP
#include "bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class RBTree;

  template< typename T, typename Compare = std::less< > >
  class ConstBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class UnbalancedBinarySearchTree< T, Compare >;
    friend class BidirectionalIterator< T, Compare >;
    friend class RBTree< T, Compare >;
   public:
    using this_t = ConstBidirectionalIterator< T, Compare >;
    ConstBidirectionalIterator();
    ConstBidirectionalIterator(const BidirectionalIterator< T, Compare > & rhs);
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
    Tree< T, Compare > * node_;
    Tree< T, Compare > * fake_;
    ConstBidirectionalIterator(Tree< T, Compare > * node, Tree< T, Compare > * fake);
  };

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare >::ConstBidirectionalIterator():
   node_(nullptr),
   fake_(nullptr)
  {}

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > & ConstBidirectionalIterator< T, Compare >::operator++()
  {
    assert(node_ != nullptr);
    if (node_->right != fake_)
    {
      node_= node_->right;
      return *this;
    }
    Tree< T > * previous = node_;
    node_ = node_->parent;
    while (node_ != fake_ && node_->right == previous)
    {
      previous = node_;
      node_ = node_->parent;
    }
    return *this;
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare >::ConstBidirectionalIterator(const BidirectionalIterator< T, Compare > & rhs):
   node_(rhs.node_),
   fake_(rhs.fake_)
  {}

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > ConstBidirectionalIterator< T, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > & ConstBidirectionalIterator< T, Compare >::operator--()
  {
    assert(node_ != nullptr);
    if (node_->left != fake_)
    {
      node_ = node_->left;
      return *this;
    }
    Tree< T > * previous = node_;
    node_ = node_->parent;
    while (node_ != fake_ && node_->left == previous)
    {
      previous = node_;
      node_ = node_->parent;
    }
    return *this;
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > ConstBidirectionalIterator< T, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    --(*this);
    return temp;
  }

  template< typename T, typename Compare >
  const T & ConstBidirectionalIterator< T, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T, typename Compare >
  const T * ConstBidirectionalIterator< T, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare >::ConstBidirectionalIterator(Tree< T, Compare > * node, Tree< T, Compare > * fake):
   node_(node),
   fake_(fake)
  {}

  template< typename T, typename Compare >
  bool operator==(const ConstBidirectionalIterator< T, Compare > & lhs, const ConstBidirectionalIterator< T, Compare > & rhs)
  {
    return lhs.operator->() == rhs.operator->();
  }

  template< typename T, typename Compare >
  bool operator!=(const ConstBidirectionalIterator< T, Compare > & lhs, const ConstBidirectionalIterator< T, Compare > & rhs)
  {
    return !(lhs == rhs);
  }
}
#endif
