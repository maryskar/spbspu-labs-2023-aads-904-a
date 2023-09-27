#ifndef TRAVERSES_HPP
#define TRAVERSES_HPP

#include <avltree.hpp>

namespace hrushchev
{ 
  template< typename F >
  F doAscending(const AVLTree< long long, std::string >& tree, F f)
  {
    f = tree.traverse_lnr(f);
    return f;
  }

  template< typename F >
  F doDescending(const AVLTree< long long, std::string >& tree, F f)
  {
    f = tree.traverse_rnl(f);
    return f;
  }

  template< typename F >
  F doBreadth(const AVLTree< long long, std::string >& tree, F f)
  {
    f = tree.traverse_breadth(f);
    return f;
  }

  template< typename F >
  using func_type = F(*)(const hrushchev::AVLTree< long long, std::string >&, F);
  template< typename F >
  AVLTree< std::string, func_type< F > > createDict()
  {
    AVLTree< std::string, func_type< F > > dict;
    dict.insert("ascending", hrushchev::doAscending);
    dict.insert("descending", hrushchev::doDescending);
    dict.insert("breadth", hrushchev::doBreadth);
    return dict;
  }
}

#endif
