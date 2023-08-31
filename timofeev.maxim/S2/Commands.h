#ifndef COMMANDS_H
#define COMMANDS_H
#include "commandSet.h"
#include "Dictionary.h"
namespace timofeev
{
  using dictionary = timofeev::Dictionary< size_t, std::string >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary >;
  void Print(std::istream& in, dictOfDicts& dict, std::ostream& out);
  void Complement(std::istream& in, dictOfDicts& dict, std::ostream& out);
  void Intersect(std::istream& in, dictOfDicts& dict, std::ostream& out);
  void Union(std::istream& in, dictOfDicts& dict, std::ostream& out);
}

#endif //S2_COMMANDS_H
