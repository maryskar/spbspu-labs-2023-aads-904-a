#include "huffman-code.hpp"

turkin::encoding_t turkin::encode(const phrase_t & phrase, const encoding_map_t & map)
{
  encoding_t result;
  for (char i: phrase)
  {
    result += map.at(i);
  }
  return result;
}
