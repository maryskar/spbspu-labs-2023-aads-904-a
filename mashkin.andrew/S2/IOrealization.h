#ifndef S2_IOREALIZATION_H
#define S2_IOREALIZATION_H
#include <iostream>
#include <string>
#include <ios>
#include "dictionary.h"

namespace mashkin
{
  using dictionary = mashkin::Dictionary< int, std::string >;
  using dictionaries = mashkin::Dictionary< std::string, dictionary >;

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();

  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& inp, dictionary& dict);
  std::istream& operator>>(std::istream& inp, dictionaries& dicts);
  std::ostream& operator<<(std::ostream& out, const dictionary& dicts);
}
#endif
