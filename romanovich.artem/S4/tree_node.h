#ifndef TREE_NODE_H
#define TREE_NODE_H
template< typename T >
struct TreeNode
{
  T data;
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;
  explicit TreeNode(const T &data);
  TreeNode< T > *findMin(TreeNode< T > *node);
  TreeNode< T > *findMax(TreeNode< T > *node);
};
template< typename T >
TreeNode< T > *TreeNode< T >::findMax(TreeNode< T > *node)
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
template< typename T >
TreeNode< T > *TreeNode< T >::findMin(TreeNode< T > *node)
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
template< typename T >
TreeNode< T >::TreeNode(const T &data):
  data(data),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
{
}
#endif
