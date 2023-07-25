#ifndef MASHKIN_ANDREW_CREATEMAPOFSORTFUNCTIONS_H
#define MASHKIN_ANDREW_CREATEMAPOFSORTFUNCTIONS_H
#include "sortFunctions.h"
#include <utility>

namespace mashkin
{
  template< class T >
  void createMapOfSortFunctions(T& map)
  {
    map["ascending"]["ints"] = ascendInt;
    /*map["ascending"]["floats"];
    map["descending"]["ints"];
    map["descending"]["floats"];*/
  }
}
#endif
