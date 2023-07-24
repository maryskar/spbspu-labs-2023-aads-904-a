#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <functional>
#include "tree_node.h"
template< typename Key, typename Value, typename Compare = std::less< Key >>
class BinarySearchTree
{
public:
  BinarySearchTree();
  ~BinarySearchTree();
  void insert(const Key &key, const Value &value);
  void remove(const Key &key);
  Value *find(const Key &key);
private:
  TreeNode< Key, Value > *root_;
  void clear(TreeNode< Key, Value > *node);
  TreeNode< Key, Value > *
  insertImpl(TreeNode< Key, Value > *node, TreeNode< Key, Value > *parent, const Key &key, const Value &value);
  TreeNode< Key, Value > *removeImpl(TreeNode< Key, Value > *node, const Key &key);
  TreeNode< Key, Value > *findMin(TreeNode< Key, Value > *node);
};
template< typename Key, typename Value, typename Compare >
TreeNode< Key, Value > *BinarySearchTree< Key, Value, Compare >::findMin(TreeNode< Key, Value > *node)
{
  if (!node)
  {
    return nullptr;
  }
  while (node->left)
  {
    node = node->left;
  }
  return node;
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
template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::insert(const Key &key, const Value &value)
{
  root_ = insertImpl(root_, nullptr, key, value);
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree():
  root_(nullptr)
{
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
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
