#ifndef IOSTREAMOVERLOADS_H
#define IOSTREAMOVERLOADS_H
#include <iostream>
#include <string>
#include <ios>
#include "dictionary.h"

namespace mashkin
{
  using dictionary = mashkin::Dictionary< int, std::string >;
  using dictionaries = mashkin::Dictionary< std::string, dictionary >;

  std::istream& operator>>(std::istream& inp, dictionary& dict);
  std::istream& operator>>(std::istream& inp, dictionaries& dicts);
  std::ostream& operator<<(std::ostream& out, const dictionary& dicts);
}
#endif
