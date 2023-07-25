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
  BidirectionalIterator(TreeNode< data_type > *root, TreeNode< data_type > *node, TreeNode< data_type > *fakeNode);
  data_type &operator*();
  data_type *operator->();
  BidirectionalIterator &operator++();
  BidirectionalIterator operator++(int);
  BidirectionalIterator &operator--();
  BidirectionalIterator operator--(int);
private:
  TreeNode< data_type > *node_;
  TreeNode< data_type > *fakeNode_;
  TreeNode< data_type > *root_;
};
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
  if (node_ == fakeNode_)
  {
    node_ = root_->findMax(root_);
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
  if (node_ == nullptr)
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
BidirectionalIterator< Key, Value, Compare >
::BidirectionalIterator(TreeNode< data_type > *root, TreeNode< data_type > *node, TreeNode< data_type > *fakeNode):
  node_(node),
  fakeNode_(fakeNode),
  root_(root)
{
}
#endif
