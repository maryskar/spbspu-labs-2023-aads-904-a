#ifndef REVERSE_CONST_ITERATOR_HPP
#define REVERSE_CONST_ITERATOR_HPP

#include <utility>
#include "tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class RBtree;
  template< typename K, typename V, typename C >
  class ReverseConstIterator
  {
    friend class RBtree< K, V, C >;
    using dcit = ReverseConstIterator< K, V, C >;
    using tree_t = std::pair< K, V >;
    using Node = TreeNode< tree_t > *;
    public:
      ReverseConstIterator();
      explicit ReverseConstIterator(Node rhs);
      dcit & operator=(const dcit & rhs) = default;
      ~ReverseConstIterator() = default;
      dcit & operator++();
      dcit operator++(int);
      dcit & operator--();
      dcit operator--(int);
      const tree_t & operator*() const;
      const tree_t * operator->() const;
      bool operator==(const dcit & rhs) const;
      bool operator!=(const dcit & rhs) const;
    private:
      Node cur_;
  };
}

#endif
