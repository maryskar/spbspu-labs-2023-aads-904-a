#ifndef CONST_BIDIRECT_ITER_H
#define CONST_BIDIRECT_ITER_H

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
  class BidirectionalIterator;

  template < typename T, typename Compare >
  class ConstBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, const T >
  {
  public:
   using bidirect_iter = BidirectionalIterator< T, Compare >;
   using this_t = ConstBidirectionalIterator< T, Compare >;
   using tree_t = details::Tree< T, Compare >;

   friend class BinarySearchTree< T, Compare >;
   friend class RedBlackTree< T, Compare >;
   friend class BidirectionalIterator< T, Compare >;

   ConstBidirectionalIterator():
     fakeNode_(nullptr),
     node_(nullptr)
   {}
   explicit ConstBidirectionalIterator(tree_t* fakeNode, tree_t* node):
     fakeNode_(fakeNode),
     node_(node)
   {}
   ConstBidirectionalIterator(const bidirect_iter& iter):
     fakeNode_(iter.fakeNode_),
     node_(iter.node_)
   {}
   ConstBidirectionalIterator(const this_t&) = default;
   ~ConstBidirectionalIterator() = default;

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
  ConstBidirectionalIterator< T, Compare >& ConstBidirectionalIterator< T, Compare >::operator++()
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
  ConstBidirectionalIterator< T, Compare > ConstBidirectionalIterator< T, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare >& ConstBidirectionalIterator< T, Compare >::operator--()
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
      while (parent != nullptr && node_ == parent->left_)
      {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
    }
    return *this;
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > ConstBidirectionalIterator< T, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T, typename Compare >
  bool ConstBidirectionalIterator< T, Compare >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T, typename Compare >
  bool ConstBidirectionalIterator< T, Compare >::operator!=(const this_t& rhs) const
  {
    return !(*this == rhs);
  }

  template< typename T, typename Compare >
  T& ConstBidirectionalIterator< T, Compare >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T, typename Compare >
  T* ConstBidirectionalIterator< T, Compare >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T, typename Compare >
  T& ConstBidirectionalIterator< T, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T, typename Compare >
  T* ConstBidirectionalIterator< T, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }
}
#endif
