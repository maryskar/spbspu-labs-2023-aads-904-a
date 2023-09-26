#include "traverses.hpp"

template< typename F >
void hrushchev::doAscending(AVLTree< size_t, std::string >& tree, F f)
{
  tree.traverse_lnr(f);
}

template< typename F >
void hrushchev::doDescending(AVLTree< size_t, std::string >& tree, F f)
{
  tree.traverse_rnl(f);
}

template< typename F >
void hrushchev::doBreadth(AVLTree< size_t, std::string >& tree, F f)
{
  tree.traverse_breadth(f);
}
