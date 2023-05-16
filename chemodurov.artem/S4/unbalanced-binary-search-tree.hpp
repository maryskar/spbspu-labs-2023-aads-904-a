#ifndef S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#define S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#include <functional>
#include "bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare = std::less<> >
  class UnbalancedBinarySearchTree
  {
    friend class BidirectionalIterator< T >;
   public:

   private:
    Tree< T, Compare > * fake_;
    Compare comp_;
    std::size_t size_;
  };
}

#endif
