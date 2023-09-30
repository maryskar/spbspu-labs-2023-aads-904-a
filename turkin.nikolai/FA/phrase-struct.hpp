#ifndef PHRASE_STRUCT_HPP
#define PHRASE_STRUCT_HPP

#include "data-types.hpp"

namespace turkin
{
  struct PType
  {
    public:
      PType(const phrase_t & phrase);
      const phrase_t & get_phrase();
      const encoding_t & get_encoding();
      const encoding_map_t & get_encoding_map();
      void set_encoding(const encoding_t & encoding);
      void set_encoding_map(const encoding_map_t & map);

    private:
      phrase_t phrase_;
      encoding_t encoding_;
      encoding_map_t map_;
  };

  using phrase_dict_t = turkin::AVLtree< phrase_t, PType, std::less< > >;
}

#endif
