#ifndef S4_TREE_HPP
#define S4_TREE_HPP
#include <functional>

namespace chemodurov
{
  template< typename T, typename Compare = std::less<> >
  struct Tree
  {
    T data;
    Tree< T, Compare > * left;
    Tree< T, Compare > * right;
    Tree< T, Compare > * parent;
  };
}

#endif
