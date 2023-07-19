#ifndef BIDIRECT_ITER_H
#define BIDIRECT_ITER_H

#include <iterator>
#include <cassert>
#include "Tree.h"

namespace tarasenko
{
  template< typename T, typename Compare >
  class BinarySearchTree;
  template< typename T, typename Compare >
  class RedBlackTree;
  template< typename T, typename Compare >
  class ConstBidirectionalIterator;

  template < typename T, typename Compare >
  class BidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
   using this_t = BidirectionalIterator< T, Compare >;
   using tree_t = details::Tree< T, Compare >;

   friend class BinarySearchTree< T, Compare >;
   friend class RedBlackTree< T, Compare >;
   friend class ConstBidirectionalIterator< T, Compare >;

   BidirectionalIterator():
     fakeNode_(nullptr),
     node_(nullptr)
   {}
   explicit BidirectionalIterator(tree_t* fakeNode, tree_t* node):
     fakeNode_(fakeNode),
     node_(node)
   {}
   BidirectionalIterator(const this_t&) = default;
   ~BidirectionalIterator() = default;

   this_t& operator=(const this_t&) = default;

   this_t& operator++();
   this_t operator++(int);

   this_t& operator--();
   this_t operator--(int);

   T& operator*();
   T* operator->();

   T& operator*() const;
   T* operator->() const;

   bool operator!=(const this_t&) const;
   bool operator==(const this_t&) const;

  private:
   tree_t* fakeNode_;
   tree_t* node_;
  };

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare >& BidirectionalIterator< T, Compare >::operator++()
  {
    assert(node_ != nullptr);
    if (node_->right_ != fakeNode_)
    {
      node_ = node_->right_;
      while (node_->left_ != fakeNode_)
      {
        node_ = node_->left_;
      }
    }
    else
    {
      tree_t* parent = node_->parent_;
      while (parent != fakeNode_ && node_ == parent->right_)
      {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
    }
    return *this;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BidirectionalIterator< T, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare >& BidirectionalIterator< T, Compare >::operator--()
  {
    assert(node_ != nullptr);
    if (node_->left_ != fakeNode_)
    {
      node_ = node_->left_;
      while (node_->right_ != fakeNode_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      tree_t* parent = node_->parent_;
      if (node_ != fakeNode_)
      {
        while (parent != fakeNode_ && node_ == parent->left_)
        {
          node_ = parent;
          parent = parent->parent_;
        }
      }
      node_ = parent;
    }
    return *this;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BidirectionalIterator< T, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T, typename Compare >
  bool BidirectionalIterator< T, Compare >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T, typename Compare >
  bool BidirectionalIterator< T, Compare >::operator!=(const this_t& rhs) const
  {
    return !(*this == rhs);
  }

  template< typename T, typename Compare >
  T& BidirectionalIterator< T, Compare >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T, typename Compare >
  T* BidirectionalIterator< T, Compare >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T, typename Compare >
  T& BidirectionalIterator< T, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T, typename Compare >
  T* BidirectionalIterator< T, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }
}
#endif
