#ifndef S4_CONST_BIDIRECTIONAL_ITERATOR_HPP
#define S4_CONST_BIDIRECTIONAL_ITERATOR_HPP
#include "bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T >
  class ConstBidirectionalIterator
  {
    friend class BidirectionalIterator< T >;
   public:
    using this_t = ConstBidirectionalIterator< T >;
    ConstBidirectionalIterator();
    ConstBidirectionalIterator(const BidirectionalIterator< T > & rhs);
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

  template< typename T >
  ConstBidirectionalIterator< T > & ConstBidirectionalIterator< T >::operator++()
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

  template< typename T >
  ConstBidirectionalIterator< T >::ConstBidirectionalIterator(const BidirectionalIterator< T > & rhs):
   node_(rhs.node_),
   fake_(rhs.fake_)
  {}

  template< typename T >
  ConstBidirectionalIterator< T > ConstBidirectionalIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  ConstBidirectionalIterator< T > & ConstBidirectionalIterator< T >::operator--()
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

  template< typename T >
  ConstBidirectionalIterator< T > ConstBidirectionalIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    --(*this);
    return temp;
  }

  template< typename T >
  const T & ConstBidirectionalIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T * ConstBidirectionalIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool operator==(const ConstBidirectionalIterator< T > & lhs, const ConstBidirectionalIterator< T > & rhs)
  {
    return lhs.operator->() == rhs.operator->();
  }

  template< typename T >
  bool operator!=(const ConstBidirectionalIterator< T > & lhs, const ConstBidirectionalIterator< T > & rhs)
  {
    return !(lhs == rhs);
  }
}
#endif
