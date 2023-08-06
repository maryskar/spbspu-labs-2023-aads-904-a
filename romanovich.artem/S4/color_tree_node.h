#ifndef COLOR_TREE_NODE_H
#define COLOR_TREE_NODE_H
#include <memory>
#include "tree_node.h"
enum class Color
{
  C_RED,
  C_BLACK
};
template< typename T, typename Tree >
class ColorTreeNode
{
public:
  explicit ColorTreeNode(const T &data, Color color = Color::C_RED);
  void setColor(Color color);
  Color getColor() const;
private:
  std::unique_ptr< TreeNode< T > > node_;
  Color color_;
};
template< typename T, typename Tree >
Color ColorTreeNode< T, Tree >::getColor() const
{
  return color_;
}
template< typename T, typename Tree >
void ColorTreeNode< T, Tree >::setColor(Color color)
{
  color_ = color;
}
template< typename T, typename Tree >
ColorTreeNode< T, Tree >::ColorTreeNode(const T &data, Color color):
  node_(std::make_unique< TreeNode< T > >(data)),
  color_(color)
{
}
template< typename Key, typename Value, typename Compare >
class BinarySearchTree;
template< typename Key, typename Value, typename Compare >
class ColorTreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > >
{
  using T = std::pair< Key, Value >;
public:
  explicit ColorTreeNode(const T &data);
private:
  std::unique_ptr< TreeNode< T > > node_;
};
template< typename Key, typename Value, typename Compare >
ColorTreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > >::ColorTreeNode(const T &data):
  node_(std::make_unique< TreeNode< T > >(data))
{
}
#endif
