#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "data-types.hpp"

namespace turkin
{
  struct PType
  {
    public:
      PType(const phrase_t & phrase);
      const phrase_t & get_phrase() const;
      const encoding_t & get_encoding() const;
      const encoding_map_t & get_char_encoding() const;
      
    private:
      phrase_t phrase_;
      encoding_t encoding_;
      encoding_map_t map_;
  };
  
  namespace details
  {
     std::pair< encoding_t, encoding_map_t > encode(const phrase_t & phrase);
     phrase_t decode(const encoding_t & encoding, const encoding_map_t & map);
     encoding_t recode(const phrase_t & phrase, encoding_map_t & map);
  }
}

#endif
