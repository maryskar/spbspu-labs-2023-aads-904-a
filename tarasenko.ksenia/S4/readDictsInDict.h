#ifndef READDICTSINDICT_H
#define READDICTSINDICT_H

#include <iostream>
#include <string>
#include "map.h"

namespace tarasenko
{
  using dict_t = Map< size_t, std::string, std::less<> >;
  void readDictsInDict(std::istream& input, Map< std::string, dict_t, std::greater<> >& dict_of_dict);
}
#endif
