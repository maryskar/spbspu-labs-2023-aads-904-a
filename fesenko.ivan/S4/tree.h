#ifndef TREE_H
#define TREE_H
namespace fesenko
{
  template< typename T >
  struct Tree
  {
    T data;
    Tree< T > *parent_;
    Tree< T > *left_;
    Tree< T > *right_;
  };
}
#endif
