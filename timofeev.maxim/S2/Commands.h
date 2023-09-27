#ifndef COMMANDS_H
#define COMMANDS_H
#include "commandSet.h"
#include "Dictionary.h"
#include "iostream"
namespace timofeev
{
  using dictionary = timofeev::Dictionary< size_t, std::string >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary >;
  void Complement(std::istream& in, dictOfDicts& dict);
  void Intersect(std::istream& in, dictOfDicts& dict);
  void Union(std::istream& in, dictOfDicts& dict);
}

#endif
