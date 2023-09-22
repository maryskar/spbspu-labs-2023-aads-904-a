#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <dictionary/dictionary.hpp>
#include <avl-tree/avl-tree.hpp>
#include <string>

namespace turkin
{
  using phrase_t = std::string;
  using encoding_t = std::string;
  using encoding_map_t = AVLtree< char, std::size_t, std::less< > >;
  using encoding_list_t = Dictionary< char, std::size_t, std::less< > >;
}

#endif
