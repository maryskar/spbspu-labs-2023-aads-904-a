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
private:
  TreeNode< Key, Value > *root;
  void clear(TreeNode< Key, Value > *node);
};
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
  clear(root);
}
template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree():
  root(nullptr)
{
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
