#ifndef HUFFMAN_CODE_HPP
#define HUFFMAN_CODE_HPP

#include "data-types.hpp"

namespace turkin
{
  encoding_t encode(const phrase_t & phrase, const encoding_map_t & map);
}

#endif
