#ifndef S2_INDICT_H
#define S2_INDICT_H
#include <istream>
#include <limits>
#include "Dictionary.h"
namespace timofeev
{
  using dictionary = timofeev::Dictionary< size_t, std::string, std::less<> >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary, std::less<> >;
  dictOfDicts inDict(std::istream& in, dictOfDicts &dict);
}
#endif
