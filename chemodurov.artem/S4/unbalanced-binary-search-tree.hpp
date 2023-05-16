#ifndef S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#define S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#include <functional>
#include "tree.hpp"

namespace chemodurov
{
  template< typename T, typename Compare = std::less<> >
  class UnbalancedBinarySearchTree
  {
   public:

   private:
    Tree< T, Compare > * fake_;
    Compare comp_;
  };
}

#endif
