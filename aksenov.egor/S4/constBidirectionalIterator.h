#ifndef CONSTConstBidirectionalIterator_H
#define CONSTConstBidirectionalIterator_H
#include <functional>
#include <cassert>
#include "tree.h"

namespace aksenov
{
  template < typename T >
  node_t< T >* getPrev(node_t< T >* node)
  {
    if (!node)
    {
      return node;
    }
    if (node->left_)
    {
      node = node->left_;
      while (node->right_)
      {
        node = node->right_;
      }
    }
    else
    {
      node_t< T >* parent = node->parent_;
      while (parent && node == parent->left_)
      {
        node = parent;
        parent = parent->parent_;
      }
      node = parent;
    }
    return node;
  }

  template < typename T >
  node_t< T >* getNext(node_t< T >* node)
  {
    if (!node)
    {
      return node;
    }
    if (node->right_)
    {
      node = node->right_;
      while (node->left_)
      {
        node = node->left_;
      }
    }
    else
    {
      node_t< T >* parent = node->parent_;
      while (parent && node == parent->right_)
      {
        node = parent;
        parent = parent->parent_;
      }
      node = parent;
    }
    return node;
  }

  template < typename T >
  class ConstBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend struct node_t< T >;
    using TreeNode = node_t< T >;
    using NodePtr = node_t< T >*;

    template < typename, typename, typename >
    friend class BinarySearchTree;
    template < typename, typename, typename >
    friend class AVL;

    ~ConstBidirectionalIterator() = default;
    ConstBidirectionalIterator(const ConstBidirectionalIterator&) = default;
    ConstBidirectionalIterator& operator=(const ConstBidirectionalIterator&) = default;

    ConstBidirectionalIterator& operator++();
    ConstBidirectionalIterator operator++(int);
    ConstBidirectionalIterator& operator--();
    ConstBidirectionalIterator operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const ConstBidirectionalIterator&) const;
    bool operator==(const ConstBidirectionalIterator&) const;
    explicit ConstBidirectionalIterator(NodePtr node):
      node_(node)
    {}
  private:
    NodePtr node_;
  };

  template < typename T >
  typename ConstBidirectionalIterator< T >::ConstBidirectionalIterator& ConstBidirectionalIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = getNext(node_);
    return *this;
  }

  template < typename T >
  typename ConstBidirectionalIterator< T >::ConstBidirectionalIterator ConstBidirectionalIterator< T >::operator++(int)
  {
    ConstBidirectionalIterator toReturn(*this);
    ++(*this);
    return toReturn;
  }

  template < typename T >
  typename ConstBidirectionalIterator< T >::ConstBidirectionalIterator& ConstBidirectionalIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = getPrev(node_);
    return *this;
  }

  template < typename T >
  typename ConstBidirectionalIterator< T >::ConstBidirectionalIterator ConstBidirectionalIterator< T >::operator--(int)
  {
    ConstBidirectionalIterator toReturn(*this);
    --(*this);
    return toReturn;
  }

  template < typename T >
  const T& ConstBidirectionalIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < typename T >
  const T* ConstBidirectionalIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < typename T >
  bool ConstBidirectionalIterator< T >::operator!=(const ConstBidirectionalIterator& other) const
  {
    return !(*this == other);
  }

  template < typename T >
  bool ConstBidirectionalIterator< T >::operator==(const ConstBidirectionalIterator& other) const
  {
    return node_ == other.node_;
  }
}
#endif

