#ifndef TREE_NODE
#define TREE_NODE

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

  template< typename T >
  void free(TreeNode< T > * source)
  {
    if (!source)
    {
      return;
    }
    free(source->left);
    free(source->right);
    delete source;
  }
}

#endif
