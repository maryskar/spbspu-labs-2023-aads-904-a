#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H
#include <iterator>
#include "tree_node.h"
namespace romanovich
{
  template< typename Key, typename Value, typename Compare >
  class ConstBidirectionalIterator;
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree;
  template< typename Key, typename Value, typename Compare >
  class RedBlackTree;
  template< typename Key, typename Value, typename Compare = std::less<> >
  class BidirectionalIterator
  {
    friend class BinarySearchTree< Key, Value, Compare >;
    friend class ConstBidirectionalIterator< Key, Value, Compare >;
    friend class RedBlackTree< Key, Value, Compare >;
  public:
    BidirectionalIterator();
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_t = std::ptrdiff_t;
    using data_t = std::pair< Key, Value >;
    using tree_node_t = TreeNode< data_t, BinarySearchTree< Key, Value, Compare > >;
    ~BidirectionalIterator() = default;
    BidirectionalIterator(const BidirectionalIterator< Key, Value, Compare > &) = default;
    explicit BidirectionalIterator(ConstBidirectionalIterator< Key, Value, Compare > &);
    explicit BidirectionalIterator(tree_node_t *root, tree_node_t *node, tree_node_t *fakeNode);
    BidirectionalIterator< Key, Value, Compare > &
    operator=(const BidirectionalIterator< Key, Value, Compare > &) = default;
    data_t &operator*();
    data_t *operator->();
    BidirectionalIterator &operator++();
    const BidirectionalIterator operator++(int);
    BidirectionalIterator &operator--();
    const BidirectionalIterator operator--(int);
    bool operator!=(const BidirectionalIterator &other) const;
    bool operator==(const BidirectionalIterator &other) const;
  private:
    tree_node_t *node_;
    tree_node_t *fakeNode_;
    tree_node_t *root_;
  };
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >::BidirectionalIterator():
    node_(nullptr),
    fakeNode_(nullptr),
    root_(nullptr)
  {
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >::BidirectionalIterator(
    ConstBidirectionalIterator< Key, Value, Compare > &rhs):
    node_(const_cast<tree_node_t *>(rhs.node_)),
    fakeNode_(const_cast<tree_node_t *>(rhs.fakeNode_)),
    root_(const_cast<tree_node_t *>(rhs.root_))
  {
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >::BidirectionalIterator(tree_node_t *root,
                                                                      tree_node_t *node,
                                                                      tree_node_t *fakeNode):
    node_(node),
    fakeNode_(fakeNode),
    root_(root)
  {
    if (!root || !fakeNode)
    {
      throw std::invalid_argument("Null pointer passed to iterator.");
    }
  }
  template< typename Key, typename Value, typename Compare >
  bool BidirectionalIterator< Key, Value, Compare >::operator==(const BidirectionalIterator &other) const
  {
    return node_ == other.node_;
  }
  template< typename Key, typename Value, typename Compare >
  bool BidirectionalIterator< Key, Value, Compare >::operator!=(const BidirectionalIterator &other) const
  {
    return !(*this == other);
  }
  template< typename Key, typename Value, typename Compare >
  const BidirectionalIterator< Key, Value, Compare > BidirectionalIterator< Key, Value, Compare >::operator--(int)
  {
    BidirectionalIterator tmp(*this);
    --(*this);
    return tmp;
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > &BidirectionalIterator< Key, Value, Compare >::operator--()
  {
    if (!node_)
    {
      throw std::runtime_error("Decrementing null iterator.");
    }
    if (node_ == fakeNode_)
    {
      return *this;
    }
    if (node_->left)
    {
      node_ = node_->left;
      while (node_->right)
      {
        node_ = node_->right;
      }
    }
    else
    {
      tree_node_t *prev = nullptr;
      do
      {
        prev = node_;
        node_ = node_->parent;
      } while (node_ && node_->left == prev);
    }
    if (!node_)
    {
      node_ = fakeNode_;
    }
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > *BidirectionalIterator< Key, Value, Compare >::operator->()
  {
    return std::addressof(operator*());;
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &BidirectionalIterator< Key, Value, Compare >::operator*()
  {
    return node_->data;
  }
  template< typename Key, typename Value, typename Compare >
  const BidirectionalIterator< Key, Value, Compare > BidirectionalIterator< Key, Value, Compare >::operator++(int)
  {
    BidirectionalIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > &BidirectionalIterator< Key, Value, Compare >::operator++()
  {
    if (!node_)
    {
      throw std::runtime_error("Incrementing null iterator.");
    }
    if (node_ == fakeNode_)
    {
      return *this;
    }
    if (node_->right)
    {
      node_ = node_->right;
      while (node_->left)
      {
        node_ = node_->left;
      }
    }
    else
    {
      tree_node_t *prev = nullptr;
      do
      {
        prev = node_;
        node_ = node_->parent;
      } while (node_ && node_->right == prev);
    }
    if (node_ == nullptr)
    {
      node_ = fakeNode_;
    }
    return *this;
  }
}
#endif
