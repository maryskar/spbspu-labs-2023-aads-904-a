#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <functional>
#include <cstddef>
#include <stdexcept>
#include "tree_node.h"
template< typename Key, typename Value, typename Compare = std::less< Key >>
class BinarySearchTree
{
public:
  using bst_t = BinarySearchTree< Key, Value, Compare >;
  using tree_t = TreeNode< Key, Value >;
  ///
  using iterator = int;
  using const_iterator = int;
  using reverse_iterator = int;
  using const_reverse_iterator = int;
  ///
  BinarySearchTree();
  ~BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &other);
  BinarySearchTree(BinarySearchTree &&other) noexcept;
  BinarySearchTree &operator=(const BinarySearchTree &other);
  BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
  //void insert(const Key &key, const Value &value);
  void remove(const Key &key);
  Value *find(const Key &key);
  ///
  /*iterator beforeBegin() const;
  iterator begin() const;
  iterator end() const;
  const_iterator cbeforeBegin() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;*/
  Value &at(const Key &key);
  const Value &at(const Key &key) const;
  Value &operator[](const Key &key);
  Value &operator[](Key &&key);
  size_t size() const;
  bool isEmpty() const;
  std::pair< iterator, bool > insert(const Key &key, const Value &value);
  std::pair< iterator, bool > insert(Key &&key, Value &&value);
  /*iterator insert(const_iterator pos, const Key &key, const Value &value);
  iterator insert(const_iterator pos, Key &&key, Value &&value);
  template< class InputIt >
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  void clear();
  iterator erase(iterator pos);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);*/
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
  void clear(TreeNode< Key, Value > *node);
  TreeNode< Key, Value > *insertImpl(TreeNode< Key, Value > *node, TreeNode< Key, Value > *parent,
                                     const Key &key, const Value &value);
  TreeNode< Key, Value > *removeImpl(TreeNode< Key, Value > *node, const Key &key);
  tree_t *initFake();
  TreeNode< Key, Value > *copyTree(const TreeNode< Key, Value > *node);
  TreeNode< Key, Value > *copyBegin(const TreeNode< Key, Value > *beginNode);
  TreeNode< Key, Value > *copyEnd(const TreeNode< Key, Value > *endNode);
};
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
  return result.first->value;
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
    if (compare_(key, node->key))
    {
      node = node->left;
    }
    else if (compare_(node->key, key))
    {
      node = node->right;
    }
    else
    {
      return node->value;
    }
  }
  throw std::out_of_range("Key not found.");
}
template< typename Key, typename Value, typename Compare >
TreeNode< Key, Value > *BinarySearchTree< Key, Value, Compare >::copyTree(const TreeNode< Key, Value > *node)
{
  if (!node)
  {
    return nullptr;
  }
  TreeNode< Key, Value > *newNode = new TreeNode< Key, Value >(node->key, node->value);
  newNode->left = copyTree(node->left);
  newNode->right = copyTree(node->right);
  if (newNode->left)
  {
    newNode->left->parent = newNode;
  }
  if (newNode->right)
  {
    newNode->right->parent = newNode;
  }
  return newNode;
}
template< typename Key, typename Value, typename Compare >
TreeNode< Key, Value > *BinarySearchTree< Key, Value, Compare >::copyBegin(const TreeNode< Key, Value > *beginNode)
{
  if (!beginNode)
  {
    return nullptr;
  }
  TreeNode< Key, Value > *newBegin = new TreeNode< Key, Value >(beginNode->key, beginNode->value);
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
TreeNode< Key, Value > *BinarySearchTree< Key, Value, Compare >::copyEnd(const TreeNode< Key, Value > *endNode)
{
  if (!endNode)
  {
    return nullptr;
  }
  TreeNode< Key, Value > *newEnd = new TreeNode< Key, Value >(endNode->key, endNode->value);
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
TreeNode< Key, Value > *BinarySearchTree< Key, Value, Compare >::initFake()
{
  void *nodeMemory = ::operator new(sizeof(BinarySearchTree::tree_t));
  BinarySearchTree::tree_t *newNode = static_cast< BinarySearchTree::tree_t >(nodeMemory);
  newNode->next_ = nullptr;
  return newNode;
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
TreeNode< Key, Value > *
BinarySearchTree< Key, Value, Compare >::removeImpl(TreeNode< Key, Value > *node, const Key &key)
{
  if (!node)
  {
    return nullptr;
  }
  Compare cmp;
  if (cmp(key, node->key))
  {
    node->left = removeImpl(node->left, key);
  }
  else if (cmp(node->key, key))
  {
    node->right = removeImpl(node->right, key);
  }
  else
  {
    if (!node->left)
    {
      TreeNode< Key, Value > *rightChild = node->right;
      if (rightChild)
      {
        rightChild->parent = node->parent;
      }
      delete node;
      return rightChild;
    }
    else if (!node->right)
    {
      TreeNode< Key, Value > *leftChild = node->left;
      if (leftChild)
      {
        leftChild->parent = node->parent;
      }
      delete node;
      return leftChild;
    }
    else
    {
      TreeNode< Key, Value > *minRight = findMin(node->right);
      node->key = minRight->key;
      node->value = minRight->value;
      node->right = removeImpl(node->right, minRight->key);
    }
  }
  return node;
}
template< typename Key, typename Value, typename Compare >
TreeNode< Key, Value > *
BinarySearchTree< Key, Value, Compare >::insertImpl(TreeNode< Key, Value > *node, TreeNode< Key, Value > *parent,
                                                    const Key &key, const Value &value)
{
  if (!node)
  {
    TreeNode< Key, Value > *newNode = new TreeNode< Key, Value >(key, value);
    newNode->parent = parent;
    return newNode;
  }
  Compare cmp;
  if (cmp(key, node->key))
  {
    node->left = insertImpl(node->left, node, key, value);
  }
  else if (cmp(node->key, key))
  {
    node->right = insertImpl(node->right, node, key, value);
  }
  else
  {
    node->value = value;
  }
  return node;
}
template< typename Key, typename Value, typename Compare >
Value *BinarySearchTree< Key, Value, Compare >::find(const Key &key)
{
  TreeNode< Key, Value > *node = root_;
  Compare cmp;
  while (node)
  {
    if (cmp(key, node->key))
    {
      node = node->left;
    }
    else if (cmp(node->key, key))
    {
      node = node->right;
    }
    else
    {
      return &node->value;
    }
  }
  return nullptr;
}
template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::remove(const Key &key)
{
  root_ = removeImpl(root_, key);
}
/*template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::insert(const Key &key, const Value &value)
{
  root_ = insertImpl(root_, nullptr, key, value);
}*/
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree():
  fakeNode_(nullptr),
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
void BinarySearchTree< Key, Value, Compare >::clear(TreeNode< Key, Value > *node)
{
  if (node)
  {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}
#endif
