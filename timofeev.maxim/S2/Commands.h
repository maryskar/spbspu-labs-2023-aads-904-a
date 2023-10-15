#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include "commandSet.h"
#include "Dictionary.h"

namespace timofeev
{
  using dictionary = timofeev::Dictionary< size_t, std::string, std::less<> >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary, std::less<> >;
  void doComplement(std::istream& in, dictOfDicts& dict);
  void doIntersect(std::istream& in, dictOfDicts& dict);
  void doUnion(std::istream& in, dictOfDicts& dict);
}

#endif
