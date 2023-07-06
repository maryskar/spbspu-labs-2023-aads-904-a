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
  void copy(TreeNode< T, C > * source)
  {
    
  }
}



#endif
