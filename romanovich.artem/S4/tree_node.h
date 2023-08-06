#ifndef TREE_NODE_H
#define TREE_NODE_H
enum class Color
{
  C_RED,
  C_BLACK
};
template< typename T >
struct TreeNode
{
  explicit TreeNode(const T &data, Color color = Color::C_RED);
  T data;
  Color color;
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;
};
template< typename T >
TreeNode< T >::TreeNode(const T &data, Color color):
  data(data),
  color(color),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
{
}
#endif
