#ifndef S4_DICTWITHCOMMANDS_H
#define S4_DICTWITHCOMMANDS_H
#include "Commands.h"

namespace mashkin
{
  template< class T >
  T createDictWithCommnads()
  {
    T dict;
    dict["print"] = print;
    dict["complement"] = complement;
    dict["intersect"] = intersect;
    dict["union"] = unionDicts;
    return dict;
  }
}
#endif
