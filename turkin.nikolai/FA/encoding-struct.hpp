#ifndef ENCODING_STRUCT_HPP
#define ENCODING_STRUCT_HPP

#include "data-types.hpp"

namespace turkin
{
  class HType
  {
    public:
      HType();
      explicit HType(const phrase_t & phrase);
      HType(const HType & htree);
      HType(HType && htree);
      HType & operator=(const HType & htree);
      HType & operator=(HType && htree);
      ~HType();

      const encoding_list_t & get_encoding_list();
      const encoding_map_t & get_encoding_map();

    private:
      void free(node_t * src);
      node_t * copy(node_t * src);
      void encode(node_t * src, encoding_t code);
      node_t * root_;
      encoding_list_t list_;
      encoding_map_t map_;
  };

  using encoding_dict_t = turkin::AVLtree< encoding_t, HType, std::less< > >;

  std::ostream & operator<<(std::ostream & out, const encoding_map_t & map);
}

#endif
