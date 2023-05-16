#ifndef S4_BIDIRECTIONAL_ITERATOR_HPP
#define S4_BIDIRECTIONAL_ITERATOR_HPP
#include <cassert>
#include "tree.hpp"

namespace chemodurov
{
  template< typename T >
  class BidirectionalIterator
  {
   public:
    using this_t = BidirectionalIterator< T >;
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
    Tree< T > * node_;
    Tree< T > * fake_;
  };

  template< typename T >
  BidirectionalIterator< T >::BidirectionalIterator():
   node_(nullptr),
   fake_(nullptr)
  {}

  template< typename T >
  BidirectionalIterator< T > & BidirectionalIterator< T >::operator++()
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
  BidirectionalIterator< T > BidirectionalIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  BidirectionalIterator< T > & BidirectionalIterator< T >::operator--()
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
  BidirectionalIterator< T > BidirectionalIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    --(*this);
    return temp;
  }

  template< typename T >
  const T & BidirectionalIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T & BidirectionalIterator< T >::operator*()
  {
    return const_cast< T & >((static_cast< const this_t >(*this)).operator*());
  }

  template< typename T >
  const T * BidirectionalIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  T * BidirectionalIterator< T >::operator->()
  {
    return const_cast< T * >((static_cast< const this_t >(*this)).operator->());
  }

  template< typename T >
  bool operator==(const BidirectionalIterator< T > & lhs, const BidirectionalIterator< T > & rhs)
  {
    return lhs.operator->() == rhs.operator->();
  }

  template< typename T >
  bool operator!=(const BidirectionalIterator< T > & lhs, const BidirectionalIterator< T > & rhs)
  {
    return !(lhs == rhs);
  }
}
#endif
