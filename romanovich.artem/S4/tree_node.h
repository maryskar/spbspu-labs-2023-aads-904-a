#ifndef COLOR_TREE_NODE_H
#define COLOR_TREE_NODE_H
#include <memory>
#include "tree_node_impl.h"
enum class Color
{
  C_RED,
  C_BLACK
};
template< typename T, typename Tree >
class TreeNode
{
public:
  explicit TreeNode(const T &data, Color color = Color::C_RED);
  void setColor(Color color);
  Color getColor() const;
private:
  std::unique_ptr< TreeNodeImpl< T > > node_;
  Color color_;
};
template< typename T, typename Tree >
Color TreeNode< T, Tree >::getColor() const
{
  return color_;
}
template< typename T, typename Tree >
void TreeNode< T, Tree >::setColor(Color color)
{
  color_ = color;
}
template< typename T, typename Tree >
TreeNode< T, Tree >::TreeNode(const T &data, Color color):
  node_(std::make_unique< TreeNodeImpl< T > >(data)),
  color_(color)
{
}
template< typename Key, typename Value, typename Compare >
class BinarySearchTree;
template< typename Key, typename Value, typename Compare >
class TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > >
{
  using T = std::pair< Key, Value >;
public:
  explicit TreeNode(const T &data);
private:
  std::unique_ptr< TreeNodeImpl< T > > node_;
};
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > >::TreeNode(const T &data):
  node_(std::make_unique< TreeNodeImpl< T > >(data))
{
}
#endif
