#ifndef TREE_H
#define TREE_H
namespace fesenko
{
  template< typename T >
  struct Tree
  {
    T data;
    Tree< T > *parent;
    Tree< T > *left;
    Tree< T > *right;
  };
}
#endif
