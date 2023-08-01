#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <functional>
#include <cstddef>
#include <stdexcept>
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
  ///
  using iterator = BidirectionalIterator< Key, Value, Compare >;
  using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;
  /////////////using reverse_iterator = int;
  /////////////using const_reverse_iterator = int;
  ///
  BinarySearchTree();
  ~BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &other);
  BinarySearchTree(BinarySearchTree &&other) noexcept;
  BinarySearchTree &operator=(const BinarySearchTree &other);
  BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
  void remove(const Key &key);
  iterator find(const Key &key);
  ///
  iterator end() const noexcept;
  const_iterator cend() const noexcept;
  /*iterator beforeBegin() const;
  const_iterator cbeforeBegin() const;*/
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
  iterator lower_bound(const Key &key);
  const_iterator lower_bound(const Key &key) const;
  iterator upper_bound(const Key &key);
  const_iterator upper_bound(const Key &key) const;
  Compare value_comp() const;
private:
  tree_t *fakeNode_;
  tree_t *root_;
  tree_t *begin_;
  tree_t *end_;
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
ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::clast() const noexcept
{
  return const_iterator(root_, fakeNode_->right, fakeNode_);
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::last() noexcept
{
  return iterator(root_, fakeNode_->right, fakeNode_);
}
template< typename Key, typename Value, typename Compare >
ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::cbegin() const noexcept
{
  return const_iterator(root_, fakeNode_->left, fakeNode_);
}
template< typename Key, typename Value, typename Compare >
BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::begin() noexcept
{
  return iterator(root_, fakeNode_->left, fakeNode_); // ошибка!!!!!!!
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
  TreeNode< data_type > *newBegin = new TreeNode< data_type >(beginNode->key, beginNode->value);
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
  TreeNode< data_type > *newEnd = new TreeNode< data_type >(endNode->key, endNode->value);
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
  begin_(other.begin_),
  end_(other.end_),
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
  BinarySearchTree::tree_t *fakeNode = static_cast< BinarySearchTree::tree_t * >(nodeMemory);
  fakeNode->parent = nullptr;
  fakeNode->left = nullptr;
  fakeNode->right = nullptr;
  return fakeNode;
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree &other):
  fakeNode_(initFake()),
  root_(nullptr),
  begin_(nullptr),
  end_(nullptr),
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
  begin_ = copyBegin(other.begin_);
  end_ = copyEnd(other.end_);
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
  if (!fakeNode_)
  {
    fakeNode_ = new TreeNode< data_type >(data_type(Key(), Value()));
  }
  fakeNode_->parent = root_;
  if (!node)
  {
    auto *newNode = new TreeNode< data_type >(data_type(key, value));
    newNode->parent = parent;
    return newNode;
  }
  if (compare_(key, node->data.first))
  {
    node->left = insertImpl(node->left, node, key, value);
    fakeNode_->left = node->left;
  }
  else if (compare_(node->data.first, key))
  {
    node->right = insertImpl(node->right, node, key, value);
    fakeNode_->right = node->right;
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
  --size_;
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
  begin_(nullptr),
  end_(nullptr),
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
  begin_ = nullptr;
  end_ = nullptr;
}
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, const Key &key, const Value &value)
{
  TreeNode< data_type > *parent = nullptr;
  TreeNode< data_type > *current = root_;
  ++size_; // тут хуйня какая-то
  while (current != nullptr)
  {
    if (compare_(key, current->data.first))
    {
      parent = current;
      current = current->left;
    }
    else if (compare_(current->data.first, key))
    {
      parent = current;
      current = current->right;
    }
    else
    {
      return iterator(current, fakeNode_);
    }
  }
  current = new TreeNode< data_type >(key, value);
  current->parent = parent;
  if (parent == nullptr)
  {
    root_ = current;
  }
  else if (compare_(key, parent->data.first))
  {
    parent->left = current;
  }
  else
  {
    parent->right = current;
  }
  return iterator(current, fakeNode_);
}
//Не работает size при Insert
template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, Key &&key, Value &&value)
{
  iterator insertPos = const_cast< iterator >(pos);
  return insert(insertPos, std::forward< Key >(key), std::forward< Value >(value));
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
#endif
