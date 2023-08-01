#ifndef DIRECT_CONST_ITERATOR_HPP
#define DIRECT_CONST_ITERATOR_HPP

#include <utility>
#include "../tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree;
  template< typename K, typename V, typename C >
  class ConstIterator
  {
    friend class AVLtree< K, V, C >;
    using cit = ConstIterator< K, V, C >;
    using tree_t = std::pair< K, V >;
    using Node = TreeNode< tree_t, C > *;
    public:
      ConstIterator();
      explicit ConstIterator(Node rhs);
      cit & operator=(const cit & rhs) = default;
      ~ConstIterator() = default;
      cit & operator++();
      cit operator++(int);
      cit & operator--();
      cit operator--(int);
      const tree_t & operator*() const;
      const tree_t * operator->() const;
      bool operator==(const cit & rhs) const;
      bool operator!=(const cit & rhs) const;
    private:
      Node cur_;
  };
}

#endif
