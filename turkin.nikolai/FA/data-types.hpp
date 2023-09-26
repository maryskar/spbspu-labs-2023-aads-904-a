#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <string>

#include <avl-tree/avl-tree.hpp>
#include <avl-tree/tree-node.hpp>
#include <queue.hpp>

namespace turkin
{
  using phrase_t = std::string;
  using encoding_t = std::string;
  using encoding_pair_t = std::pair< char, std::size_t >;
  using encoding_map_t = AVLtree< char, encoding_t, std::less< > >;
  using node_t = TreeNode< encoding_pair_t >;
  using encoding_list_t = AVLtree< char, node_t *, std::less< > >;
  using queue_t = Queue< node_t * >;
}

#endif
