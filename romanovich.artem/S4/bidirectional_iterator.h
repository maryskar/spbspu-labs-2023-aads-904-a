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
  BidirectionalIterator(TreeNode< Key, Value > *root, TreeNode< Key, Value > *node, TreeNode< Key, Value > *fakeNode);
  BidirectionalIterator &operator*();
  BidirectionalIterator *operator->() const;
  BidirectionalIterator &operator++();
  BidirectionalIterator operator++(int);
  BidirectionalIterator &operator--();
  BidirectionalIterator operator--(int);
private:
  TreeNode< Key, Value > *current_;
  TreeNode< Key, Value > *fakeNode_;
  TreeNode< Key, Value > *root_;
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
  if (current_ == fakeNode_)
  {
    current_ = findMax(root_);
    return *this;
  }
  if (current_->left)
  {
    current_ = current_->left;
    while (current_->right)
    {
      current_ = current_->right;
    }
  }
  else
  {
    TreeNode< Key, Value > *prev = nullptr;
    do
    {
      prev = current_;
      current_ = current_->parent;
    } while (current_ && current_->left == prev);
  }
  if (current_ == nullptr)
  {
    current_ = fakeNode_;
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > *BidirectionalIterator< Key, Value, Compare >::operator->() const
{
  return std::addressof(*(*this));
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > &BidirectionalIterator< Key, Value, Compare >::operator*()
{
  if (current_ == fakeNode_)
  {
    throw std::out_of_range("Iterator is out of range.");
  }
  return std::make_pair(current_->key, current_->value);
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
  if (current_ == fakeNode_)
  {
    return *this;
  }
  if (current_->right)
  {
    current_ = current_->right;
    while (current_->left)
    {
      current_ = current_->left;
    }
  }
  else
  {
    TreeNode< Key, Value > *prev = nullptr;
    do
    {
      prev = current_;
      current_ = current_->parent;
    } while (current_ && current_->right == prev);
  }
  if (current_ == nullptr)
  {
    current_ = fakeNode_;
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare >
::BidirectionalIterator(TreeNode< Key, Value > *root, TreeNode< Key, Value > *node, TreeNode< Key, Value > *fakeNode):
  current_(node),
  fakeNode_(fakeNode),
  root_(root)
{
}
#endif
