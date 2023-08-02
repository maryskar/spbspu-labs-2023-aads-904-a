#ifndef CONST_BIDIRECTIONAL_ITERATOR_H
#define CONST_BIDIRECTIONAL_ITERATOR_H
#include <iterator>
#include "tree_node.h"
#include "iterator_data.h"
template< typename Key, typename Value, typename Compare = std::less< Key > >
class ConstBidirectionalIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using data_type = std::pair< Key, Value >;
  using const_data_type = const std::pair< Key, Value >;
  ~ConstBidirectionalIterator() = default;
  ConstBidirectionalIterator(const ConstBidirectionalIterator< Key, Value, Compare > &) = default;
  explicit ConstBidirectionalIterator(const IteratorData< data_type > &dto);
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
  const TreeNode< data_type > *getNode() const;
  const TreeNode< data_type > *getFakeNode() const;
  const TreeNode< data_type > *getRoot() const;
  template< typename NonConstIterator >
  NonConstIterator asNonConst();
private:
  const TreeNode< data_type > *node_;
  const TreeNode< data_type > *fakeNode_;
  const TreeNode< data_type > *root_;
};
template< typename Key, typename Value, typename Compare >
template< typename NonConstIterator >
NonConstIterator ConstBidirectionalIterator< Key, Value, Compare >::asNonConst()
{
  return NonConstIterator(IteratorData< data_type >{root_, node_, fakeNode_});
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare >::ConstBidirectionalIterator(const IteratorData< data_type > &dto):
  node_(dto.node),
  fakeNode_(dto.fakeNode),
  root_(dto.root)
{
  if (!dto.root || !dto.fakeNode)
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
template< typename Key, typename Value, typename Compare >
const TreeNode< typename ConstBidirectionalIterator< Key, Value, Compare >::data_type > *
ConstBidirectionalIterator< Key, Value, Compare >::getNode() const
{
  return node_;
}
template< typename Key, typename Value, typename Compare >
const TreeNode< typename ConstBidirectionalIterator< Key, Value, Compare >::data_type > *
ConstBidirectionalIterator< Key, Value, Compare >::getFakeNode() const
{
  return fakeNode_;
}
template< typename Key, typename Value, typename Compare >
const TreeNode< typename ConstBidirectionalIterator< Key, Value, Compare >::data_type > *
ConstBidirectionalIterator< Key, Value, Compare >::getRoot() const
{
  return root_;
}
#endif
