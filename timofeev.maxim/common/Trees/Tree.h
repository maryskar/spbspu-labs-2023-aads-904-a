#ifndef S4_TREE_H
#define S4_TREE_H
#include "cstddef"
namespace timofeev
{
  template< class T >
  struct Tree
  {
    T data;
    Tree< T >* parent_;
    Tree< T >* left_;
    Tree< T >* right_;
    size_t height;
  };
  template< typename T >
  bool empty(const Tree< T >* node) noexcept
  {
    return node == nullptr;
  }
  template< typename T >
  void clearTree(Tree< T >* parent)
  {
    if (empty(parent))
    {
      return;
    }
    else if (!empty(parent->left_))
    {
      clear(parent->left_);
    }
    else if (!empty(parent->right_))
    {
      clear(parent->right_);
    }
    delete parent;
  }
}

#endif
