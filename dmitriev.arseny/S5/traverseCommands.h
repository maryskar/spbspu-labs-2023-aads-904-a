#ifndef TRAVERSECOMMANDS_H
#define TRAVERSECOMMANDS_H

#include <AVL.h>

namespace dmitriev
{
  template< typename F >
  F doAscending(const AVL< const int, std::string >& tree, F f)
  {
    f = tree.traverseLnr(f);
    return f;
  }

  template< typename F >
  F doDescending(const AVL< const int, std::string >& tree, F f)
  {
    f = tree.traverseRnl(f);
    return f;
  }

  template< typename F >
  F doBreadth(const AVL< const int, std::string >& tree, F f)
  {
    f = tree.traverseBreadth(f);
    return f;
  }
}

#endif
