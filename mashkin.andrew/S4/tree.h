#ifndef S4_TREE_H
#define S4_TREE_H
#include <functional>

namespace mashkin
{
  template< class T, class Comporator = std::less< T > >
  struct Tree
  {
    T data;
    Tree< T >* left;
    Tree< T >* right;
    Comporator comp;
  };
}
#endif
