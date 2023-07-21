#ifndef INPUTDICT_HPP
#define INPUTDICT_HPP

#include <istream>
#include <string>
#include "dictionary.hpp"

namespace hrushchev
{
  using dict_t = Dictionary< size_t, std::string >;

  void inputDict(std::istream& input, Dictionary< std::string, dict_t >& dict_of_dict);
}

#endif
