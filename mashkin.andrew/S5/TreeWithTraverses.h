#ifndef MASHKIN_ANDREW_TREEWITHTRAVERSES_H
#define MASHKIN_ANDREW_TREEWITHTRAVERSES_H
#include "Traverses.h"

namespace mashkin
{
  AVL< std::string, void (*)(std::ostream&, AVL< int, std::string >&) > createTreeWithTraverses()
  {
    AVL< std::string, void (*)(std::ostream&, AVL< int, std::string >&) > dict;
    dict["ascending"] = ascend;
    dict["descending"] = descend;
    dict["breadth"] = doBreadthTr;
    return dict;
  }
}
#endif
