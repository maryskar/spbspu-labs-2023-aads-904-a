#ifndef S4_TREE_H
#define S4_TREE_H
#include <functional>

namespace mashkin
{
  template< class T >
  struct Tree
  {
    T data;
    Tree< T >* parent_;
    Tree< T >* left_;
    Tree< T >* right_;
  };
}
#endif
