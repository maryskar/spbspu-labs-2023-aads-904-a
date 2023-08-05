#ifndef COLOR_TREE_NODE_H
#define COLOR_TREE_NODE_H
#include "tree_node.h"
enum class Color
{
  C_RED,
  C_BLACK
};
template< typename T >
class ColorTreeNode
{
public:
  explicit ColorTreeNode(const T &data, Color color = Color::C_RED);
  TreeNode< T > *getNode() const;
  void setColor(Color color);
  Color getColor() const;
private:
  TreeNode< T > *node_;
  Color color_;
};
template< typename T >
Color ColorTreeNode< T >::getColor() const
{
  return color_;
}
template< typename T >
void ColorTreeNode< T >::setColor(Color color)
{
  color_ = color;
}
template< typename T >
TreeNode< T > *ColorTreeNode< T >::getNode() const
{
  return node_;
}
template< typename T >
ColorTreeNode< T >::ColorTreeNode(const T &data, Color color):
  node_(new TreeNode< T >(data)),
  color_(color)
{
}
#endif
