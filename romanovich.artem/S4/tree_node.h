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
struct TreeNode
{
  explicit TreeNode(const T &data, Color color = Color::C_RED);
  TreeNodeImpl< T > *nodeImpl; //std::unique_ptr< TreeNodeImpl< T > > nodeImpl;
  Color color;
};
template< typename T, typename Tree >
TreeNode< T, Tree >::TreeNode(const T &data, Color color):
  nodeImpl(TreeNodeImpl< T >(data)),
  color(color)
{
}
template< typename Key, typename Value, typename Compare >
class BinarySearchTree;
template< typename Key, typename Value, typename Compare >
struct TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > >
{
  using T = std::pair< Key, Value >;
  explicit TreeNode(const T &data);
  TreeNodeImpl< T > *nodeImpl; //std::unique_ptr< TreeNodeImpl< T > > nodeImpl;
};
template< typename Key, typename Value, typename Compare >
TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > >::TreeNode(const T &data):
  nodeImpl(TreeNodeImpl< T >(data))
{
}
#endif
