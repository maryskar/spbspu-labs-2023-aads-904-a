#ifndef MASHKIN_ANDREW_CREATEMAPOFSORTFUNCTIONS_H
#define MASHKIN_ANDREW_CREATEMAPOFSORTFUNCTIONS_H
#include "sortFunctions.h"
#include <AVL/AVL.h>
#include <utility>

namespace mashkin
{
  AVL< std::string, AVL< std::string, void (*)(std::ostream&, size_t) > > createMapOfSortFunctions()
  {
    AVL< std::string, AVL< std::string, void (*)(std::ostream&, size_t) > > map;
    map["ascending"]["ints"] = ascendInt;
    map["ascending"]["floats"] = ascendFloat;
    map["descending"]["ints"] = descendInt;
    map["descending"]["floats"] = descendFloat;
    return map;
  }
}
#endif
