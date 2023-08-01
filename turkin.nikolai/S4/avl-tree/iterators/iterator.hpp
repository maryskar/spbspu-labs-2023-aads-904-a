#ifndef DIRECT_ITERATOR_HPP
#define DIRECT_ITERATOR_HPP

#include <utility>
#include "../tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree;
  template< typename K, typename V, typename C >
  class Iterator
  {
    friend class AVLtree< K, V, C >;
    using it = Iterator< K, V, C >;
    using tree_t = std::pair< K, V >;
    using Node = TreeNode< tree_t > *;
    public:
      Iterator();
      explicit Iterator(Node rhs);
      it & operator=(const it & rhs) = default;
      ~Iterator() = default;
      it & operator++();
      it operator++(int);
      it & operator--();
      it operator--(int);
      tree_t & operator*();
      tree_t * operator->();
      bool operator==(const it & rhs) const;
      bool operator!=(const it & rhs) const;
    private:
      Node cur_;
  };
}

#endif
  