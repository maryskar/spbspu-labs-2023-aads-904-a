#ifndef S4_TREE_H
#define S4_TREE_H

namespace mashkin
{
  template< class T, class Comporator >
  struct Tree
  {
    T data;
    Tree< T, Comporator >* left;
    Tree< T, Comporator >* right;
    Comporator comp;
  };
}
#endif
