#ifndef READ_DICTS_IN_DICT_H
#define READ_DICTS_IN_DICT_H

#include <iostream>
#include <string>
#include <compare.h>
#include "dictionary.h"

namespace tarasenko
{
  using dict_t = Dictionary< size_t, std::string, tarasenko::Comp >;
  void readDictsInDict(std::istream& input, Dictionary< std::string, dict_t, std::greater<> >& dict_of_dict);
}
#endif
