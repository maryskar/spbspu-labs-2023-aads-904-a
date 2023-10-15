#ifndef COMMANDSET_H
#define COMMANDSET_H
#include <string>
#include "Dictionary.h"
namespace timofeev
{
  using dictionary = timofeev::Dictionary< size_t, std::string, std::less<> >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary, std::less<> >;
  using comDict = Dictionary< std::string, void (*)(std::istream&, dictOfDicts&) >;
  void Print(std::istream& in, dictOfDicts& dict, std::ostream& out);
  comDict cmdSet();
}
#endif
