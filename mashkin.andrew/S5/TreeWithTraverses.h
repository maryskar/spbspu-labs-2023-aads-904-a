#ifndef MASHKIN_ANDREW_TREEWITHTRAVERSES_H
#define MASHKIN_ANDREW_TREEWITHTRAVERSES_H
#include "Traverses.h"

namespace mashkin
{
  template< class T >
  void createTreeWithTraverses(T& dict)
  {
    dict["ascending"] = ascend;
    dict["descending"] = descend;
    dict["breadth"] = doBreadthTr;
  }
}
#endif
