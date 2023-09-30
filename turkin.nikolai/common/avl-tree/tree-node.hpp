#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace turkin
{
  template< typename T >
  struct TreeNode
  {
    T data;
    TreeNode< T > * parent;
    TreeNode< T > * left;
    TreeNode< T > * right;
    int height;
  };
}

#endif
