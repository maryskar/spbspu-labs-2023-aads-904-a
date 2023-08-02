#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "tree_node.h"
#include "bidirectional_iterator.h"
#include "const_bidirectional_iterator.h"
template< typename Key, typename Value, typename Compare = std::less< Key >>
class BinarySearchTree
{
public:
  using data_type = std::pair< Key, Value >;
  using bst_t = BinarySearchTree< Key, Value, Compare >;
  using tree_t = TreeNode< data_type >;
  using iterator = BidirectionalIterator< Key, Value, Compare >;
  using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;
  //using reverse_iterator = int;
  //using const_reverse_iterator = int;
  BinarySearchTree();
  ~BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &other);
  BinarySearchTree(BinarySearchTree &&other) noexcept;
  BinarySearchTree &operator=(const BinarySearchTree &other);
  BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
  void remove(const Key &key);
  iterator find(const Key &key);
  iterator end() const noexcept;
  const_iterator cend() const noexcept;
  iterator last() noexcept;
  const_iterator clast() const noexcept;
  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  /*reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;*/
  Value &at(const Key &key);
  const Value &at(const Key &key) const;
  Value &operator[](const Key &key);
  Value &operator[](Key &&key);
  size_t size() const;
  bool empty() const;
  std::pair< iterator, bool > insert(Key &&key, Value &&value);
  std::pair< iterator, bool > insert(const Key &key, const Value &value);
  iterator insert(const_iterator pos, const Key &key, const Value &value);
  iterator insert(const_iterator pos, Key &&key, Value &&value);
  template< class InputIt >
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  void clear();
  iterator erase(iterator pos);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  size_t erase(const Key &key);
  size_t count(const Key &key) const;
  void swap(bst_t &other);
  iterator lower_bound(const Value &value);
  const_iterator lower_bound(const Value &value) const;
  iterator upper_bound(const Key &key);
  const_iterator upper_bound(const Key &key) const;
  Compare value_comp() const;
private:
  tree_t *fakeNode_;
  tree_t *root_;
//  tree_t *begin_;
//  tree_t *end_;
  size_t size_;
  Compare compare_;
  void clear(TreeNode< data_type > *node);
  TreeNode< data_type > *insertImpl(TreeNode< data_type > *node, TreeNode< data_type > *parent,
                                    const Key &key, const Value &value);
  TreeNode< data_type > *removeImpl(TreeNode< data_type > *node, const Key &key);
  tree_t *initFake();
  TreeNode< data_type > *copyBegin(const TreeNode< data_type > *beginNode);
  TreeNode< data_type > *copyEnd(const TreeNode< data_type > *endNode);
};
template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::swap(BinarySearchTree::bst_t &other)
{
  using std::swap;
  swap(fakeNode_, other.fakeNode_);
  swap(root_, other.root_);
  swap(size_, other.size_);
  swap(compare_, other.compare_);
}
template< typename Key, typename Value, typename Compare >
size_t BinarySearchTree< Key, Value, Compare >::count(const Key &key) const
{
  size_t count = 0;
  const_iterator it = lower_bound(key);
  while (it != end() && it->first == key)
  {
    ++count;
    ++it;
  }
  return count;
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::const_iterator
BinarySearchTree< Key, Value, Compare >::upper_bound(const Key &key) const
{
  return const_iterator(upper_bound(key));
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::upper_bound(const Key &key)
{
  iterator it = begin();
  while (it != end() && compare(key, it->first))
  {
    ++it;
  }
  return it;
}
template< typename Key, typename Value, typename Compare >
Compare BinarySearchTree< Key, Value, Compare >::value_comp() const
{
  return compare_;
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::const_iterator
BinarySearchTree< Key, Value, Compare >::lower_bound(const Value &value) const
{
  return const_iterator(this->lower_bound(value));
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::lower_bound(const Value &value)
{
  TreeNode< data_type > *tmp = fakeNode_->left;
  while (tmp != fakeNode_)
  {
    if (compare_(value, tmp->data))
    {
      if (tmp->left != fakeNode_)
      {
        tmp = tmp->left;
      }
      else
      {
        return const_iterator(root_, tmp, fakeNode_);
      }
    }
    else if (!compare_(value, tmp->data_) && !compare_(tmp->data_, value))
    {
      return const_iterator(tmp, fakeNode_);
    }
    else
    {
      if (tmp->right != fakeNode_)
      {
        tmp = tmp->right;
      }
      else
      {
        return ++const_iterator(tmp, fakeNode_);
      }
    }
  }
  return cend();
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::clast() const noexcept
{
  return const_iterator(root_, root_->findMax(root_), fakeNode_);
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::last() noexcept
{
  return iterator(root_, root_->findMax(root_), fakeNode_);
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::cbegin() const noexcept
{
  return const_iterator(root_, root_->findMin(root_), fakeNode_);
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::begin() noexcept
{
  return iterator(root_, root_->findMin(root_), fakeNode_);
}
template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::empty() const
{
  return root_ == nullptr;
}
template< typename Key, typename Value, typename Compare >
size_t BinarySearchTree< Key, Value, Compare >::size() const
{
  return size_;
}
template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::clear()
{
  clear(root_);
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::end() const noexcept
{
  return iterator(root_, fakeNode_, fakeNode_);
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::cend() const noexcept
{
  return const_iterator(root_, fakeNode_, fakeNode_);
}
template< typename Key, typename Value, typename Compare >
std::pair< typename BinarySearchTree< Key, Value, Compare >::iterator, bool >
BinarySearchTree< Key, Value, Compare >::insert(Key &&key, Value &&value)
{
  data_type new_data(std::forward< Key >(key), std::forward< Value >(value));
  const Key &const_key = new_data.first;
  const Value &const_value = new_data.second;
  return insert(const_key, const_value);
}
template< typename Key, typename Value, typename Compare >
Value &BinarySearchTree< Key, Value, Compare >::operator[](const Key &key)
{
  std::pair< iterator, bool > result = insert(key, Value{});
  return result.first->value;
}
template< typename Key, typename Value, typename Compare >
Value &BinarySearchTree< Key, Value, Compare >::operator[](Key &&key)
{
  std::pair< iterator, bool > result = insert(std::move(key), Value{});
  return result.first->second;
}
template< typename Key, typename Value, typename Compare >
Value &BinarySearchTree< Key, Value, Compare >::at(const Key &key)
{
  const BinarySearchTree *constThis = this;
  return const_cast<Value &>(constThis->at(key));
}
template< typename Key, typename Value, typename Compare >
const Value &BinarySearchTree< Key, Value, Compare >::at(const Key &key) const
{
  tree_t *node = root_;
  while (node)
  {
    if (compare_(key, node->data.first))
    {
      node = node->left;
    }
    else if (compare_(node->data.first, key))
    {
      node = node->right;
    }
    else
    {
      return node->data.second;
    }
  }
  throw std::out_of_range("Key not found.");
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *
BinarySearchTree< Key, Value, Compare >::copyBegin(const TreeNode< data_type > *beginNode)
{
  if (!beginNode)
  {
    return nullptr;
  }
  auto *newBegin = new TreeNode< data_type >(beginNode->key, beginNode->value);
  newBegin->left = copyBegin(beginNode->left);
  newBegin->right = copyBegin(beginNode->right);
  if (newBegin->left)
  {
    newBegin->left->parent = newBegin;
  }
  if (newBegin->right)
  {
    newBegin->right->parent = newBegin;
  }
  return newBegin;
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *
BinarySearchTree< Key, Value, Compare >::copyEnd(const TreeNode< data_type > *endNode)
{
  if (!endNode)
  {
    return nullptr;
  }
  auto *newEnd = new TreeNode< data_type >(endNode->key, endNode->value);
  newEnd->left = copyEnd(endNode->left);
  newEnd->right = copyEnd(endNode->right);
  if (newEnd->left)
  {
    newEnd->left->parent = newEnd;
  }
  if (newEnd->right)
  {
    newEnd->right->parent = newEnd;
  }
  return newEnd;
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare > &
BinarySearchTree< Key, Value, Compare >::operator=(BinarySearchTree &&other) noexcept
{
  if (this != std::addressof(other))
  {
    bst_t tmp(std::move(other));
    clear();
    swap(tmp);
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare > &
BinarySearchTree< Key, Value, Compare >::operator=(const BinarySearchTree &other)
{
  if (this != std::addressof(other))
  {
    bst_t tmp(other);
    clear();
    swap(tmp);
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree(BinarySearchTree &&other) noexcept:
  fakeNode_(other.fakeNode_),
  root_(other.root_),
//  begin_(other.begin_),
//  end_(other.end_),
  size_(other.size_),
  compare_(other.compare_)
{
  other.fakeNode_ = nullptr;
  other.root_ = nullptr;
  other.begin_ = nullptr;
  other.end_ = nullptr;
  other.size_ = 0;
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::initFake()
{
  void *nodeMemory = ::operator new(sizeof(BinarySearchTree::tree_t));
  auto *fakeNode = static_cast< BinarySearchTree::tree_t * >(nodeMemory);
  fakeNode->parent = nullptr;
  fakeNode->left = nullptr;
  fakeNode->right = nullptr;
  return fakeNode;
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree &other):
  fakeNode_(initFake()),
  root_(nullptr),
//  begin_(nullptr),
//  end_(nullptr),
  compare_(other.compare_),
  size_(0)
{
  try
  {
    root_ = copyTree(other.root_);
  }
  catch (...)
  {
    clear();
    delete fakeNode_;
    throw;
  }
//  begin_ = copyBegin(other.begin_);
//  end_ = copyEnd(other.end_);
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *
BinarySearchTree< Key, Value, Compare >::removeImpl(TreeNode< data_type > *node, const Key &key)
{
  if (!node)
  {
    return nullptr;
  }
  if (compare_(key, node->data.first))
  {
    node->left = removeImpl(node->left, key);
  }
  else if (compare_(node->data.first, key))
  {
    node->right = removeImpl(node->right, key);
  }
  else
  {
    if (!node->left)
    {
      TreeNode< data_type > *rightChild = node->right;
      if (rightChild)
      {
        rightChild->parent = node->parent;
      }
      --size_;
      delete node;
      return rightChild;
    }
    else if (!node->right)
    {
      TreeNode< data_type > *leftChild = node->left;
      if (leftChild)
      {
        leftChild->parent = node->parent;
      }
      --size_;
      delete node;
      return leftChild;
    }
    else
    {
      TreeNode< data_type > *minRight = root_->findMin(node->right);
      node->data.first = minRight->data.first;
      node->data.second = minRight->data.second;
      node->right = removeImpl(node->right, minRight->data.first);
    }
  }
  return node;
}
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::insertImpl(TreeNode< data_type > *node,
                                                                                         TreeNode< data_type > *parent,
                                                                                         const Key &key,
                                                                                         const Value &value)
{
  if (!node)
  {
    auto *newNode = new TreeNode< data_type >(data_type(key, value));
    newNode->parent = parent;
    return newNode;
  }
  if (compare_(key, node->data.first))
  {
    node->left = insertImpl(node->left, node, key, value);
    node->left->parent = node;
  }
  else if (compare_(node->data.first, key))
  {
    node->right = insertImpl(node->right, node, key, value);
    node->right->parent = node;
  }
  else
  {
    node->data.second = value;
  }
  return node;
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::find(const Key &key)
{
  tree_t *current = root_;
  while (current != nullptr)
  {
    if (compare_(current->data.first, key))
    {
      current = current->right;
    }
    else if (compare_(key, current->data.first))
    {
      current = current->left;
    }
    else
    {
      return iterator(current, fakeNode_);
    }
  }
  return end();
}
template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::remove(const Key &key)
{
  root_ = removeImpl(root_, key);
}
template< typename Key, typename Value, typename Compare >
std::pair< typename BinarySearchTree< Key, Value, Compare >::iterator, bool >
BinarySearchTree< Key, Value, Compare >::insert(const Key &key, const Value &value)
{
  root_ = insertImpl(root_, nullptr, key, value);
  ++size_;
  iterator it = find(key);
  if (it == end())
  {
    return std::make_pair(end(), false);
  }
  else
  {
    return std::make_pair(it, true);
  }
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree():
  fakeNode_(initFake()),
  root_(nullptr),
//  begin_(nullptr),
//  end_(nullptr),
  size_(0),
  compare_()
{
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
  delete fakeNode_;
  clear(root_);
}
template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::clear(TreeNode< data_type > *node)
{
  if (node)
  {
    clear(node->left);
    clear(node->right);
    delete node;
  }
  root_ = nullptr;
//  begin_ = nullptr;
//  end_ = nullptr;
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, const Key &key, const Value &value)
{
  if (!pos.node_)
  {
    return insertImpl(nullptr, nullptr, key, value);
  }
  else if (compare_(key, pos.node_->data.first))
  {
    if (!pos.node_->left)
    {
      return insertImpl(nullptr, pos.node_, key, value);
    }
    else
    {
      return insertImpl(pos.node_->left, pos.node_, key, value);
    }
  }
  else
  {
    if (!pos.node_->right)
    {
      return insertImpl(nullptr, pos.node_, key, value);
    }
    else
    {
      return insertImpl(pos.node_->right, pos.node_, key, value);
    }
  }
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, Key &&key, Value &&value)
{
  return insert(pos, std::forward< Key >(key), std::forward< Value >(value));
}
template< typename Key, typename Value, typename Compare >
template< class InputIt >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, InputIt first, InputIt last)
{
  iterator result;
  for (InputIt it = first; it != last; ++it)
  {
    result = insert(pos, it->first, it->second);
  }
  return result;
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator BinarySearchTree< Key, Value, Compare >::erase(iterator pos)
{
  if (pos == end() || pos.getNode() == fakeNode_)
  {
    throw std::out_of_range("Invalid iterator for erase.");
  }
  tree_t *node = pos.getNode();
  tree_t *parent = node->parent;
  tree_t *next_node = nullptr;
  if (node->right)
  {
    next_node = node->right;
    while (next_node->left)
    {
      next_node = next_node->left;
    }
  }
  else if (node->left)
  {
    next_node = node->left;
    while (next_node->right)
    {
      next_node = next_node->right;
    }
  }
  if (!parent)
  {
    root_ = next_node;
  }
  else if (parent->left == node)
  {
    parent->left = next_node;
  }
  else
  {
    parent->right = next_node;
  }
  delete node;
  --size_;
  return iterator(next_node, fakeNode_);
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::erase(const_iterator pos)
{
  iterator it(const_cast<tree_t *>(pos.node_), const_cast<tree_t *>(pos.fakeNode_));
  return erase(it);
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::erase(const_iterator first, const_iterator last)
{
  iterator it_first(const_cast<tree_t * >(first.getNode()), const_cast<tree_t * >(first.getFakeNode()));
  iterator it_last(const_cast<tree_t * >(last.getNode()), const_cast<tree_t * >(last.getFakeNode()));
  while (it_first != it_last)
  {
    auto next = it_first;
    ++next;
    erase(it_first);
    it_first = next;
  }
  return it_first;
}
template< typename Key, typename Value, typename Compare >
size_t BinarySearchTree< Key, Value, Compare >::erase(const Key &key)
{
  size_t count = 0;
  iterator it = find(key);
  while (it != end() && it->first == key)
  {
    iterator next = it;
    ++next;
    erase(it);
    it = next;
    ++count;
  }
  return count;
}
#endif
