#ifndef COMMANDSET_H
#define COMMANDSET_H
#include <string>
#include "Dictionary.h"
namespace timofeev
{
  using dictionary = timofeev::Dictionary< size_t, std::string >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary >;
  void Print(std::istream& in, dictOfDicts& dict, std::ostream& out);
  void cmdSet(Dictionary< std::string, void (*)(std::istream&, dictOfDicts& dict, std::ostream& out) >& command);
}
#endif
