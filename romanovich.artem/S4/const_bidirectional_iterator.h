#ifndef CONST_BIDIRECTIONAL_ITERATOR_H
#define CONST_BIDIRECTIONAL_ITERATOR_H
#include <iterator>
#include "bidirectional_iterator.h"
template< typename Key, typename Value, typename Compare >
class ConstBidirectionalIterator
{
public:
  friend class BinarySearchTree< Key, Value, Compare >;
  friend class BidirectionalIterator< Key, Value, Compare >;
  friend class RedBlackTree< Key, Value, Compare >;
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using data_type = std::pair< Key, Value >;
  using const_data_type = const std::pair< Key, Value >;
  ~ConstBidirectionalIterator() = default;
  ConstBidirectionalIterator();
  ConstBidirectionalIterator(const ConstBidirectionalIterator< Key, Value, Compare > &) = default;
  explicit ConstBidirectionalIterator(const BidirectionalIterator< Key, Value, Compare > &);
  explicit ConstBidirectionalIterator(TreeNode< data_type > *root, TreeNode< data_type > *node, TreeNode< data_type > *fakeNode);
  ConstBidirectionalIterator< Key, Value, Compare > &
  operator=(const ConstBidirectionalIterator< Key, Value, Compare > &) = default;
  const_data_type &operator*() const;
  const_data_type *operator->() const;
  ConstBidirectionalIterator< Key, Value, Compare > &operator++();
  ConstBidirectionalIterator< Key, Value, Compare > operator++(int);
  ConstBidirectionalIterator< Key, Value, Compare > &operator--();
  ConstBidirectionalIterator< Key, Value, Compare > operator--(int);
  bool operator!=(const ConstBidirectionalIterator< Key, Value, Compare > &other) const;
  bool operator==(const ConstBidirectionalIterator< Key, Value, Compare > &other) const;
private:
  const TreeNode< data_type > *node_;
  const TreeNode< data_type > *fakeNode_;
  const TreeNode< data_type > *root_;
};
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare >::ConstBidirectionalIterator():
  node_(nullptr),
  fakeNode_(nullptr),
  root_(nullptr)
{
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare >::ConstBidirectionalIterator(
  const BidirectionalIterator< Key, Value, Compare > &rhs):
  node_(rhs.node_),
  fakeNode_(rhs.fakeNode_),
  root_(rhs.root_)
{
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare >::ConstBidirectionalIterator(TreeNode< data_type > *root,
                                                                              TreeNode< data_type > *node,
                                                                              TreeNode< data_type > *fakeNode):
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
const std::pair< Key, Value > &ConstBidirectionalIterator< Key, Value, Compare >::operator*() const
{
  return node_->data;
}
template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *ConstBidirectionalIterator< Key, Value, Compare >::operator->() const
{
  return std::addressof(operator*());
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > &ConstBidirectionalIterator< Key, Value, Compare >::operator++()
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
    const TreeNode< data_type > *prev = nullptr;
    do
    {
      prev = node_;
      node_ = node_->parent;
    } while (node_ && node_->right == prev);
  }
  if (!node_)
  {
    node_ = fakeNode_;
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > ConstBidirectionalIterator< Key, Value, Compare >::operator++(int)
{
  ConstBidirectionalIterator< Key, Value, Compare > tmp(*this);
  ++(*this);
  return tmp;
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > &ConstBidirectionalIterator< Key, Value, Compare >::operator--()
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
    const TreeNode< data_type > *prev = nullptr;
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
ConstBidirectionalIterator< Key, Value, Compare > ConstBidirectionalIterator< Key, Value, Compare >::operator--(int)
{
  ConstBidirectionalIterator< Key, Value, Compare > tmp(*this);
  --(*this);
  return tmp;
}
template< typename Key, typename Value, typename Compare >
bool ConstBidirectionalIterator< Key, Value, Compare >::operator==(
  const ConstBidirectionalIterator< Key, Value, Compare > &other) const
{
  return node_ == other.node_;
}
template< typename Key, typename Value, typename Compare >
bool ConstBidirectionalIterator< Key, Value, Compare >::operator!=(
  const ConstBidirectionalIterator< Key, Value, Compare > &other) const
{
  return !(*this == other);
}
#endif
