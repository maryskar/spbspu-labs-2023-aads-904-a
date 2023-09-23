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
    public:
      explicit HTree(const phrase_t & phrase);
      ~HTree();
    private:
      void free(node_t * src);
      void encode(node_t * src, encoding_t code);
      node_t * root_;
      encoding_list_t list_;
      encoding_map_t map_;
  };
}

#endif
