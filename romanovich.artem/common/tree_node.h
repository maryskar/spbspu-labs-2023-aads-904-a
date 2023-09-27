#ifndef TREE_NODE_H
#define TREE_NODE_H
namespace romanovich
{
  namespace details
  {
    enum class Color
    {
      red,
      black
    };
  }
  template< typename T >
  struct TreeNode
  {
    explicit TreeNode(const T &data, details::Color color = details::Color::red);
    T data;
    details::Color color;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
  };
  template< typename T >
  TreeNode< T >::TreeNode(const T &data, details::Color color):
    data(data),
    color(color),
    parent(nullptr),
    left(nullptr),
    right(nullptr)
  {
  }
}
#endif
