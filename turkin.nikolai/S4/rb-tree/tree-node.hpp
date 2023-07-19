#ifndef TREE_NODE
#define TREE_NODE

namespace turkin
{
  enum class TreeColor
  {
    RED, BLACK
  };
  
  template< typename T, typename C >
  struct TreeNode
  {
    T data;
    TreeNode< T, C > * parent;
    TreeNode< T, C > * left;
    TreeNode< T, C > * right;
    TreeColor color;
    C cmp;
  };
  
  template< typename T, typename C >
  void free(TreeNode< T, C > * source)
  {
    if (source->left)
    {
      free(source->left);
    }
    if (source->right)
    {
      free(source->right);
    }
    delete source->left;
    delete source->right;
  }
  
  template< typename T, typename C >
  TreeNode< T, C > * copy(TreeNode< T, C > * source)
  {

  }

  template< typename T, typename C >
  void rotateLeft(TreeNode< T, C > * lhs)
  {
    TreeNode< T, C > * rhs = lhs->right;
    lhs->right = rhs->left;
    rhs->left = lhs;
  }

  template< typename T, typename C >
  void rotateRight(TreeNode< T, C > * rhs)
  {
    TreeNode< T, C > * lhs = rhs->right;
    rhs->left = lhs->right;
    lhs->left = rhs;
  }
}



#endif
