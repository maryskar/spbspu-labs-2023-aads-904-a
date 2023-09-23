#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "data-types.hpp"

namespace turkin
{
  struct PType
  {
    public:
      PType(const phrase_t & phrase);
      const phrase_t & get_phrase();
      const encoding_t & get_encoding();
      const encoding_map_t & get_char_encoding();
      
    private:
      phrase_t phrase_;
      encoding_t encoding_;
      encoding_map_t map_;
  };
  
  namespace details
  {
    encoding_t encode(const phrase_t & phrase, const encoding_map_t & map);
    phrase_t decode(const encoding_t & encoding, const encoding_map_t & map);
    encoding_t recode(const phrase_t & phrase, encoding_map_t & map);
  }
}

#endif
