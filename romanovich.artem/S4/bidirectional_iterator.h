#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H
#include <iterator>
#include "tree_node.h"
template< typename Key, typename Value, typename Compare >
class BidirectionalIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using data_type = std::pair< Key, Value >;
  BidirectionalIterator(const TreeNode< data_type > *root, const TreeNode< data_type > *node,
                        const TreeNode< data_type > *fakeNode);
  ~BidirectionalIterator() = default;
  BidirectionalIterator(const BidirectionalIterator< Key, Value, Compare > &) = default;
  BidirectionalIterator(TreeNode< data_type > *otherNode, TreeNode< data_type > *otherFakeNode);
  BidirectionalIterator< Key, Value, Compare > &
  operator=(const BidirectionalIterator< Key, Value, Compare > &) = default;
  data_type &operator*();
  data_type *operator->();
  BidirectionalIterator &operator++();
  BidirectionalIterator operator++(int);
  TreeNode< data_type > *getNode() const;
  BidirectionalIterator &operator--();
  BidirectionalIterator operator--(int);
  bool operator!=(const BidirectionalIterator &other) const;
  bool operator==(const BidirectionalIterator &other) const;
  TreeNode< data_type > *getFakeNode() const;
  TreeNode< data_type > *getRoot() const;
private:
  TreeNode< data_type > *node_;
  TreeNode< data_type > *fakeNode_;
  TreeNode< data_type > *root_;
};
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare >::BidirectionalIterator(TreeNode< data_type > *otherNode,
                                                                    TreeNode< data_type > *otherFakeNode):
  node_(otherNode),
  fakeNode_(otherFakeNode)
{
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *BidirectionalIterator< Key, Value, Compare >::getFakeNode() const
{
  return fakeNode_;
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *BidirectionalIterator< Key, Value, Compare >::getRoot() const
{
  return root_;
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *BidirectionalIterator< Key, Value, Compare >::getNode() const
{
  return node_;
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
BidirectionalIterator< Key, Value, Compare > BidirectionalIterator< Key, Value, Compare >::operator--(int)
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
    TreeNode< data_type > *prev = nullptr;
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
BidirectionalIterator< Key, Value, Compare > BidirectionalIterator< Key, Value, Compare >::operator++(int)
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
    TreeNode< data_type > *prev = nullptr;
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
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare >::BidirectionalIterator(const TreeNode< data_type > *root,
                                                                    const TreeNode< data_type > *node,
                                                                    const TreeNode< data_type > *fakeNode):
  node_(node),
  fakeNode_(fakeNode),
  root_(root)
{
  if (!root || !fakeNode)
  {
    throw std::invalid_argument("Null pointer passed to iterator.");
  }
}
#endif
