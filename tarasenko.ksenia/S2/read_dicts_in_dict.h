#ifndef READ_DICTS_IN_DICT_H
#define READ_DICTS_IN_DICT_H

#include <iostream>
#include <string>
#include "dictionary.h"
#include <compare.h>

namespace tarasenko
{
  using dict_t = Dictionary< size_t, std::string, Comp >;
  void readDictsInDict(std::istream& input, Dictionary< std::string, dict_t, std::greater<> >& dict_of_dict);
}
#endif
