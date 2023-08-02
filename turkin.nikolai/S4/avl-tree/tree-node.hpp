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
  void free(TreeNode< T > * src)
  {
    if (src == nullptr)
    {
      return;
    }
    if (src->left)
    free(src->left);
    free(src->right);
    delete src;
  }
}

#endif
