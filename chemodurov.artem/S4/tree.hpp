#ifndef S4_TREE_HPP
#define S4_TREE_HPP
#include <functional>

namespace chemodurov
{
  template< typename T, typename Compare = std::less<> >
  struct Tree
  {
    T data_;
    Tree< T, Compare > * left_;
    Tree< T, Compare > * right_;
    Tree< T, Compare > * parent_;
    char color_;
  };
}

#endif
