#ifndef S2_COMMANDS_H
#define S2_COMMANDS_H
#include <iostream>
#include <string>
#include "dictionary.h"

namespace mashkin
{
  using dict = mashkin::Dictionary< int, std::string >;
  using dictionaries = mashkin::Dictionary< std::string, dict >;
  void print(std::istream& inp, dictionaries& dicts);
  void complement(std::istream& inp, dictionaries& dicts);
}
#endif
