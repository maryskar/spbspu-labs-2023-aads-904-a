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
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = BidirectionalIterator< value_type >;
    using const_iterator = ConstBidirectionalIterator< value_type >;
    using this_t = UnbalancedBinarySearchTree< value_type, key_compare >;
    UnbalancedBinarySearchTree();
    UnbalancedBinarySearchTree(const this_t & other);
    UnbalancedBinarySearchTree(this_t && other);
    UnbalancedBinarySearchTree(const key_compare & comp);
    template< typename InputIt >
    UnbalancedBinarySearchTree(InputIt first, InputIt last, const key_compare & comp = key_compare());
    UnbalancedBinarySearchTree(std::initializer_list< value_type > init, const key_compare & comp = key_compare());
    ~UnbalancedBinarySearchTree();
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< value_type > init);
   private:
    Tree< T, Compare > * fake_;
    Compare comp_;
    std::size_t size_;
  };
}

#endif
