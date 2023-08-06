#ifndef TREE_NODE_H
#define TREE_NODE_H
template< typename T >
struct TreeNodeImpl
{
  T data;
  TreeNodeImpl *parent;
  TreeNodeImpl *left;
  TreeNodeImpl *right;
  explicit TreeNodeImpl(const T &data);
  TreeNodeImpl< T > *findMin(TreeNodeImpl< T > *node);
  TreeNodeImpl< T > *findMax(TreeNodeImpl< T > *node);
  TreeNodeImpl< T > *copyTree(const TreeNodeImpl< T > *node);
};
template< typename T >
TreeNodeImpl< T > *TreeNodeImpl< T >::findMax(TreeNodeImpl< T > *node)
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
TreeNodeImpl< T > *TreeNodeImpl< T >::findMin(TreeNodeImpl< T > *node)
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
TreeNodeImpl< T >::TreeNodeImpl(const T &data):
  data(data),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
{
}
template< typename T >
TreeNodeImpl< T > * TreeNodeImpl< T >::copyTree(const TreeNodeImpl< T > *node)
{
  if (!node)
  {
    return nullptr;
  }
  auto *newNode = new TreeNodeImpl< T >(node->key, node->value);
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
#endif
