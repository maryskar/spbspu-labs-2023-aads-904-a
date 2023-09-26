#ifndef TRAVERSES_HPP
#define TRAVERSES_HPP

#include <avltree.hpp>

namespace hrushchev
{ 
  void doAscending(std::ostream& out, AVLTree< size_t, std::string >& tree);
  void doDescending(std::ostream& out, AVLTree< size_t, std::string >& tree);
  void doBreadth(std::ostream& out, AVLTree< size_t, std::string >& tree);
}

#endif
