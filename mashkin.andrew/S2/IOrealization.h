#ifndef S2_IOREALIZATION_H
#define S2_IOREALIZATION_H
#include <iostream>
#include <string>
#include "dictionary.h"

namespace mashkin
{
  using dictionary = mashkin::Dictionary< int, std::string >;
  using dictionaries = mashkin::Dictionary< std::string, dictionary >;

  std::istream& operator>>(std::istream& inp, dictionary& dict);
  std::istream& operator>>(std::istream& inp, dictionaries& dicts);
}
#endif
