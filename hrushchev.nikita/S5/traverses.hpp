#ifndef TRAVERSES_HPP
#define TRAVERSES_HPP

#include <avltree.hpp>

namespace hrushchev
{ 
  template< typename F >
  void doAscending(AVLTree< size_t, std::string >& tree, F f);
  template< typename F >
  void doDescending(AVLTree< size_t, std::string >& tree, F f);
  template< typename F >
  void doBreadth(AVLTree< size_t, std::string >& tree, F f);
}

#endif
