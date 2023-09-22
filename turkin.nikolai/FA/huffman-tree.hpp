#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <cstddef>
#include <utility>
#include <functional>

#include "data-types.hpp"

#include <avl-tree/tree-node.hpp>

namespace turkin
{
  class HTree
  {
    using tree_t = std::pair< char, std::size_t >;
    using node_t = TreeNode< tree_t >;

    public:
      explicit HTree(const phrase_t & phrase);

    private:
      node_t * root_;
      encoding_list_t list_;
  };
}

#endif
