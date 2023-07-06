#ifndef DIRECT_ITERATOR_HPP
#define DIRECT_ITERATOR_HPP

#include <utility>
#include "tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class RBtree;
  template< typename K, typename V, typename C >
  class DirectIterator
  {
    friend class RBtree< K, V, C >;
    using dcit = DirectIterator< K, V, C >;
    using tree_t = std::pair< K, V >;
    using Node = TreeNode< tree_t, C > *;
    public:
      DirectIterator();
      explicit DirectIterator(Node rhs);
      dcit & operator=(const dcit & rhs) = default;
      ~DirectIterator() = default;
      dcit & operator++();
      dcit operator++(int);
      dcit & operator--();
      dcit operator--(int);
      tree_t & operator*();
      tree_t * operator->();
      bool operator==(const dcit & rhs) const;
      bool operator!=(const dcit & rhs) const;
    private:
      Node cur_;
  };
}

#endif
  