#ifndef MAPNODE_H
#define MAPNODE_H

namespace dmitriev
{
  template< typename Key, typename Value >
  struct MapNode
  {
    const size_t index;
    const Key key;
    Value value;
  };
}

#endif
