#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <forwardList.h>
#include "mapNode.h"

namespace dmitriev
{
  template < typename Key, typename Value, typename Compare = std::equal_to< Key >, typename Hash = std::hash< Key > >
  class UnorderedMap
  {
  public:
    using dataPair = std::pair< const Key, Value >;
    using dataType = MapNode< Key, Value >;
    using fList = ForwardList< dataType >;
    using iterator = typename fList::iterator;
    using constIterator = typename fList::constIterator;


  private:
    fList m_values;

    size_t m_size;
    size_t m_capacity;
    iterator* m_arr;

    Compare m_cmp;
    Hash m_hash;

  };
}



#endif
