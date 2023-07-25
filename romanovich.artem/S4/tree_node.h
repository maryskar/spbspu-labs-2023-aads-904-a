#ifndef TREE_NODE_H
#define TREE_NODE_H
template< typename Key, typename Value >
struct TreeNode
{
  Key key;
  Value value;
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;
  TreeNode(const Key &key, const Value &value);
  TreeNode< Key, Value > *findMin(TreeNode< Key, Value > *node);
  TreeNode< Key, Value > *findMax(TreeNode< Key, Value > *node);
};
template< typename Key, typename Value >
TreeNode< Key, Value > *TreeNode< Key, Value >::findMax(TreeNode< Key, Value > *node)
{
  if (!node)
  {
    return nullptr;
  }
  while (node->right)
  {
    node = node->right;
  }
  return node;
}
template< typename Key, typename Value >
TreeNode< Key, Value > *TreeNode< Key, Value >::findMin(TreeNode< Key, Value > *node)
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
template< typename Key, typename Value >
TreeNode< Key, Value >::TreeNode(const Key &key, const Value &value):
  key(key),
  value(value),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
{
}
#endif
