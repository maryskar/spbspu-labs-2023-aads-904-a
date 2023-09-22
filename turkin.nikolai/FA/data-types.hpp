#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <dictionary/forward-list/forward-list.hpp>
#include <avl-tree/avl-tree.hpp>
#include <string>

namespace turkin
{
  using phrase_t = std::string;
  using encoding_t = std::string;
  using encoding_pair_t = std::pair< char, std::size_t >;
  using encoding_map_t = AVLtree< char, std::size_t, std::less< > >;
  using encoding_list_t = ForwardList< encoding_pair_t >;
}

#endif
